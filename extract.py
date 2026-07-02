#!/usr/bin/env python3
import os
import re
import sys

SRC = "/home/alien/far2l/snippets/src/snippets.cpp"


def main() -> int:
    out_dir = os.path.dirname(os.path.abspath(sys.argv[0]))
    if len(sys.argv) >= 2:
        out_dir = os.path.abspath(sys.argv[1])

    with open(SRC, "r", encoding="utf-8") as f:
        text = f.read()

    start = text.find("SNIPPETS[] = {")
    end = text.find("*** END OF SNIPPET TABLE ***", start if start >= 0 else 0)
    if start < 0 or end < 0:
        print("could not locate SNIPPETS[] bounds in " + SRC, file=sys.stderr)
        return 1
    region = text[start:end]

    entry = re.compile(
        r'\{\s*L"([A-Za-z_][A-Za-z0-9_]*)"\s*,\s*LR"snip\(([\s\S]*?)\)snip"\s*\}'
    )

    kept = set()
    count = 0
    for m in entry.finditer(region):
        keyword, body = m.group(1), m.group(2)
        path = os.path.join(out_dir, keyword + ".cpp")
        with open(path, "w", encoding="utf-8") as f:
            f.write(body)
        kept.add(keyword + ".cpp")
        count += 1

    for name in os.listdir(out_dir):
        if name.endswith(".cpp") and name not in kept:
            os.remove(os.path.join(out_dir, name))

    print("wrote %d snippet files to %s" % (count, out_dir))
    return 0


if __name__ == "__main__":
    sys.exit(main())
