#!/bin/env python3
import subprocess as sp
import socket
import yaml
import argparse
import sys


def perror(message: str):
    print(f"{message}", file=sys.stderr)


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


def initServer():
    sp.Popen("./CnetworkingServer", stdout=sp.PIPE, stderr=sp.PIPE, stdin=sp.PIPE)


class client:
    def initSocket(self, serverAddr: str = "localhost", serverPort: int = 9001):
        self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.s.connect((serverAddr, serverPort))

    def closeSocket(self):
        self.s.close()

    def sendCommand(self, data: str):
        self.s.sendall(data.encode())
        return self.s.recv(2048).decode()


def getTest(file: str):
    with open(file) as f:
        data = yaml.safe_load(f)
    return data


def no_helo():
    print("no_helo")


def helo():
    print("helo")


def main():
    arg = parseArgs()

    scopeList = getTest(arg.testFile)
    for scope in scopeList:
        if arg.scopeList is not None:  # or scope["scope"]["name"] not in arg.scopeList:
            perror("not in scope")
            sys.exit(1)

        for test in scope["scope"]["tests"]:
            test = test["test"]
            globalsList = globals()
            print(test)
            if test["start"] in globalsList:
                globalsList[test["start"]]()


if __name__ == "__main__":
    main()
