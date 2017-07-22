import sys
import subprocess

def build():
    if len(sys.argv) != 2:
        print ("Please provide the PA# you want to test as an argument.")
        sys.exit(0)
    else:
        module = str(sys.argv[1])

    PA = module.split("/")[0]
    sub_module = module.split("/")[1]

    command = "g++ -o " + module + "/" + sub_module + ".exe " + module + "/" + sub_module + ".cpp -std=c++11 -Wall -Werror"
    p = subprocess.Popen(["exec " + command], shell=True, stderr=subprocess.STDOUT)
    p.wait()

    return sub_module + ".exe"

if __name__ == "__main__":
    build()
    print ("Done building.")
