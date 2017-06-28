import subprocess
import sys
import time
import build
from os import walk
from threading import Timer
# import threading

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

def printWithColor(color, string):
    return color + string + bcolors.ENDC

def main():
    module = ""
    timeout = 500
    # print 'Number of arguments:', len(sys.argv), 'arguments.'
    # print 'Argument List:', str(sys.argv)
    if len(sys.argv) != 2:
        print ("Please provide the module you want to test as an argument (e.g. 'PA1/evacuation')")
        sys.exit(0)
    else:
        module = str(sys.argv[1])

    # Get the file list in test directory
    f = []
    # test_folder = raw_input("test folder?")
    for (dirpath, dirnames, filenames) in walk(module + "/tests"):
    # for (dirpath, dirnames, filenames) in walk(test_folder):
        for input_filename in filenames:
            if input_filename[0:5] == 'input':
                f.append(input_filename)
        break
    f.sort()

    if len(f) == 0:
        print ("No tests found.")
        sys.exit(0)

    # TODO: compile code if executable is not there
    print ("")
    print (printWithColor(bcolors.OKGREEN, "[==========] ") + str(len(f)) + " test cases.")
    passed = 0
    failed = []
    total_time = 0

    exe_filename = ""
    # Determine executable name.
    for (dirpath, dirnames, filenames) in walk(module):
        for filename in filenames:
            if filename.endswith('.exe'):
                exe_filename = filename
                break
        break
    if exe_filename == "":
        try:
            input_build = input("No executables found. Build? (Y/n)")
        except ValueError:
            print ("Error value, exiting program.")
            sys.exit(0)
        if input_build == 'Y' or input_build == 'y':
            exe_filename = build.build()
        else:
            print ("Did not build.")

    # print(exe_filename)

    # For each pair of tests
    for i in range(0, len(f)):
        command = "./" + module + "/" + exe_filename + " " + module + "/tests/" + f[i]

        test_name = "tests/" + f[i]
        # print (command)
        print (printWithColor(bcolors.OKGREEN, "[ RUN      ] ") + module + "/" + test_name)

        ts_start = time.time()
        p = subprocess.Popen(["exec " + command], shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        try:
            p.wait(timeout=timeout)
        except subprocess.TimeoutExpired:
            p.kill()
            print (printWithColor(bcolors.FAIL, "[  FAILED  ] ") + str(timeout) + " second time out. ")
            failed.append(test_name)

        ts_total = time.time() - ts_start
        total_time = total_time + ts_total

        for idx, line in enumerate(p.stdout.readlines()):
            content = ""
            input_filename = f[i]
            output_filename = module + "/tests/output" + input_filename[5:]
            with open(output_filename) as ff:
                content = ff.readlines()
                # print (content)

            if line.decode("utf-8")  == content[idx]:
                print (printWithColor(bcolors.OKGREEN, "[       OK ] ") + module + "/" + test_name + " (" + str(int(ts_total * 1000)) + " ms)")
                passed = passed + 1
            else:
                print (printWithColor(bcolors.FAIL, "Failure "))
                print ("Expected: " + printWithColor(bcolors.OKGREEN, content[0].rstrip()))
                print ("Actual:   " + printWithColor(bcolors.FAIL, line.decode("utf-8")))
                failed.append(test_name)

    print ("")
    print (printWithColor(bcolors.OKGREEN, "[==========] ") + str(len(f)) + " tests ran. (" + str(int(total_time * 1000)) + " ms)")
    print (printWithColor(bcolors.OKGREEN, "[  PASSED  ] ") + str(passed) + " tests.")
    if len(failed) > 0:
        print (printWithColor(bcolors.FAIL, "[  FAILED  ] ") + str(len(failed)) + " tests, listed below:")

        for name in failed:
            print (printWithColor(bcolors.FAIL, "[  FAILED  ] ") + name)
    print ("")

if __name__ == "__main__":
    main()
