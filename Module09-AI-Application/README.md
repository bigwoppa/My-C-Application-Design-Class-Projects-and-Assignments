# Module 09: Using AI to Expand My Application

## My feature: a record search assistant

I would add an AI assistant that lets a user ask a question like “find Morgan” instead of remembering a record ID. It would interpret the request and suggest matching records. The user would see the record ID and name, or a clear message when nothing matches. This would make the existing record manager easier to use as the number of records grows.

## What data it needs

The feature needs the user’s search request and the IDs and names of records that user is allowed to view. It does not need passwords or unrelated personal information. My prototype uses the same three fictional example records as Module 8. A production version would use the current records, with permission checks before any data is sent to an AI service.

## Where AI fits in my architecture

The current application has a `RecordManager` for storing and searching records, plus `User`, `Admin`, and `RegularUser` classes for the menu permissions. I would place a separate `SearchAssistant` service between the user menu and `RecordManager`.

The flow would be: user request -> input validation -> assistant interprets search terms -> RecordManager looks up actual records -> application displays verified matches. AI would interpret the request; the record manager would remain the source of truth. Both roles could use the read-only assistant. The assistant would not add or delete records or decide user permissions.

## Mock prototype

`main.cpp` is a standalone, runnable mock of this feature. It uses a `MockSearchAssistant` class and simple case-insensitive keyword matching instead of calling a live AI model. It recognizes requests such as `find Morgan`, `show Avery`, and `search Jordan Lee`. It checks for blank and overly long requests, handles no matches, and lets the user try again. Type `quit` to exit.

The prototype only displays real entries from its small example vector. It makes no network calls, requires no API key, and is labeled as a mock so its output cannot be mistaken for a live model response. It demonstrates the interaction and service boundary; it is not yet connected to the Module 8 menu.

## Example

```text
Search request: find Morgan
[Mock assistant] Matching records:
ID: 102 | Name: Morgan Diaz

Search request: find Casey
[Mock assistant] No matching records. Try a name such as Morgan.
```

## How to run

From this folder:

```sh
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o search_assistant
```

Windows: `./search_assistant.exe`

macOS/Linux: `./search_assistant`

## Next steps

I would replace the mock interpretation with a live model behind the same service boundary, test varied wording and ambiguous names, and validate every returned record ID against RecordManager before displaying a result. If the model cannot identify a match or the service is unavailable, the normal ID search would still work.
