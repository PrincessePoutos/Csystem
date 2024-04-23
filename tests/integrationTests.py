#!./venv/bin/python3
import subprocess as sp
import time
import socket
import yaml
import argparse
import sys
from termcolor import cprint
import difflib
import random


def perror(message: str) -> None:
    print(f"{message}", file=sys.stderr)


def testFail(testName: str, outFail: str, out: str) -> None:
    cprint("NOK", "red", end=" ")
    print(f"{testName} : ")
    print(out.encode())
    print(outFail.encode())
    diff = difflib.unified_diff(
        out.splitlines(keepends=True),
        outFail.splitlines(keepends=True),
        fromfile="ref",
        tofile="testExcution",
    )
    perror("\n".join(diff))


def testSuccess(testName: str) -> None:
    cprint("OK", "green", end=" ")
    print(f"{testName}")


def parseArgs():
    parser = argparse.ArgumentParser(add_help=True, description="test suite")
    parser.add_argument(
        "--testFile",
        default="tests/integrationTests.yaml",
        type=str,
        help="path of file yaml for list of test",
    )
    parser.add_argument(
        "--scope", dest="scopeList", nargs="+", help="run test for list of scope"
    )

    return parser.parse_args()


def initServer() -> None:
    sp.Popen("./CnetworkingServer", stdout=logFile, stderr=logFile)


class client:
    def __init__(self) -> None:
        self.fruits = ["peach", "mango", "kiwi"]
        self.initSocket()

    def initSocket(self, serverAddr: str = "localhost", serverPort: int = 9001):
        self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.s.settimeout(1.5)
        self.s.connect((serverAddr, serverPort))

    def closeSocket(self):
        self.sendCommand("q")
        self.s.close()

    def sendCommand(self, data: str):
        self.s.sendall(data.encode() + b"\n")
        return self.s.recv(2048).decode().replace("\x00", "")

    def helo(self):
        self.sendCommand("helo sd.fr")

    def sendfruit(self):
        self.helo()
        for fruit in self.fruits:
            self.sendCommand(f"sendfruit {fruit} {random.randint(10,20)}")


def getTest(file: str):
    with open(file) as f:
        data = yaml.safe_load(f)
    return data


def getEnableErase():
    with open("./config.h") as f:
        lines = f.readlines()
    for line in lines:
        if "#define ENABLE_ERASE 1" in line:
            return True
    return False


def main():
    returnCode: int = 0
    arg = parseArgs()

    scopeList = getTest(arg.testFile)
    enableErase = getEnableErase()
    for scope in scopeList:
        if enableErase and scope["scope"]["name"] == "server_disable_erase":
            continue
        if not enableErase and scope["scope"]["name"] == "server_enable_erase":
            continue
        for test in scope["scope"]["tests"]:
            test = test["test"]
            initServer()

            time.sleep(0.1)
            c = client()
            try:
                funcStart = getattr(c, test["start"])
                funcStart()
            except:
                continue
            finally:
                out: str = c.sendCommand(test["in"])
                if out == test["out"]:
                    testSuccess(test["name"])
                else:
                    testFail(test["name"], out, test["out"])
                    returnCode = -1

                try:
                    c.closeSocket()
                except:
                    continue
    sys.exit(returnCode)


if __name__ == "__main__":
    logFile = open("integrationTests.log", "w")
    main()
    logFile.close()
