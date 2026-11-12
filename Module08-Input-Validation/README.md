# Module 08: Input Validation

This version builds on my Module 7 record manager. Admins can add, view, search, and delete records. Regular users can only view and search. Records stay sorted by ID for binary search.

## Where I used input validation

- `readInteger()` reads a whole line and checks that it contains exactly one whole number. Letters, decimals, extra text such as `12abc`, and integer overflow are rejected.
- Menu choices are limited to their actual options: 0-2 for roles and regular users, and 0-4 for admins.
- Record IDs must be positive integers. Zero and negative IDs are rejected before adding, searching, or deleting.
- `readName()` trims surrounding spaces and rejects empty or whitespace-only names and names longer than 80 characters. It displays a useful message and asks again.
- `RecordManager::addRecord()` also checks ID, name, and duplicate IDs before changing the vector. A duplicate is rejected without changing existing data.
- End-of-input is handled with an exception so the application exits safely instead of looping forever.

I use validation before accepting data so an invalid entry cannot corrupt a record or select an unintended menu action. This application has ID and name fields; it does not collect dates. Role selection demonstrates permissions and is not a secure login system. Records are held in memory for this module.

## How to run

From this folder:

```sh
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o record_manager
```

Windows: `./record_manager.exe`

macOS/Linux: `./record_manager`

## Validation examples to try

| Input | Expected behavior |
| --- | --- |
| `abc`, `1.5`, or `1abc` at a menu | Show whole-number error and retry |
| `9` at the role menu | Show range error and retry |
| `-5` or `0` as a record ID | Reject and retry |
| Blank or spaces-only name | Reject and retry |
| More than 80 characters in a name | Reject and retry |
| Existing ID `101` when adding | Report duplicate; keep original |
| ID `104` and name `  Sam Lee  ` | Add as `Sam Lee` |
| Search for `104` after adding | Display the new record |

No external libraries or live services are required.
