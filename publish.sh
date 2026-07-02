#!/bin/bash
set -euo pipefail
cd "$(dirname "$0")"

python3 extract.py .

if [[ -z "$(git status --porcelain)" ]]; then
    echo "no changes to publish"
    exit 0
fi

MSG="${1:-sync snippets}"
git add -A
git commit -m "$MSG"
git push
echo "published: $MSG"
