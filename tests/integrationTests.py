#!./venv/bin/python3
import subprocess as sp
import time
import socket
import yaml
import argparse
import sys
from termcolor import cprint
import difflib


def perror(message: str) -> None:
    print(f"{message}", file=sys.stderr)


def testFail(testName: str, outFail: str, out: str) -> None:
    cprint("NOK", "red", end=" ")
    print(f"{testName} : ")
    print(out)
    print(outFail)
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
    sp.Popen("./CnetworkingServer", stdout=sp.PIPE, stderr=sp.PIPE, stdin=sp.PIPE)


class client:
    def __init__(self) -> None:
        self.initSocket()

    def initSocket(self, serverAddr: str = "localhost", serverPort: int = 9001):
        self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.s.connect((serverAddr, serverPort))

    def closeSocket(self):
        self.sendCommand("q")
        self.s.close()

    def sendCommand(self, data: str):
        self.s.sendall(data.encode() + b"\n")
        return self.s.recv(2048).decode()

    def helo(self):
        self.sendCommand("helo sd.fr")


def getTest(file: str):
    with open(file) as f:
        data = yaml.safe_load(f)
    return data


def main():
    arg = parseArgs()

    scopeList = getTest(arg.testFile)
    for scope in scopeList:
        for test in scope["scope"]["tests"]:
            test = test["test"]
            initServer()

            time.sleep(0.00000001)
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

                try:
                    c.closeSocket()
                except:
                    continue


if __name__ == "__main__":
    main()
