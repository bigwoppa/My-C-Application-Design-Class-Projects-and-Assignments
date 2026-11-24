# Module 10: C++ and AI Performance

## Where PyTorch uses C++

I picked PyTorch because it shows how Python and C++ can work together in an AI system. Python is the interface many developers use to write experiments and train models. When the Python interface requests a tensor operation, much of the underlying work goes through native code. The C++ frontend, available through LibTorch, also lets a C++ program work with tensors and run neural networks directly on the CPU or GPU. That is useful when a model needs to run inside an existing C++ application or a service where delays matter.

Source: [PyTorch C++ Frontend documentation](https://docs.pytorch.org/cppdocs/frontend.html)

## Where C++ would help my application

My Module 9 record search assistant looks through a small list of records to find a name. That makes sense for the prototype. If the record manager grew to hundreds of thousands of entries, I would first stop converting every name to lowercase on every search. I would store a lowercase copy when a record is added or updated and use that copy for searches.

If that still felt slow, I would add a C++ index that maps chunks of three letters to the IDs of records that contain them. A search for `morgan` could intersect the candidate lists for `mor`, `org`, `rga`, and `gan`, then check the full name on the remaining records. Queries shorter than three letters would still use a scan so partial-name searches would keep working. The record manager would check permissions before showing any match.

I would compare the current scan and the indexed search on the same records and queries. I'd check that they return the same results, then measure how long searches take and how much memory the index adds. I would only keep the index if the faster searches were worth the extra memory and the work of updating it when records change.
