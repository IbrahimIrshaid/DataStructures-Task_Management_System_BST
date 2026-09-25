# Task Manager on a Binary Search Tree

![C](https://img.shields.io/badge/C-00599C?logo=c&logoColor=white)
![Data structures](https://img.shields.io/badge/structure-BST-555)

This is the [linked-list task manager](https://github.com/IbrahimIrshaid/DataStructures-Task_Management_System) rebuilt on a **binary search tree**. The interesting part is **re-keying**: the same set of tasks can be rebuilt into a new BST ordered by **ID, name, date or duration**, so different queries get an efficient ordering.

- Recursive insert, delete and search.
- **Restructure** traverses the tree and re-inserts every node into a fresh BST under a new key. Dates are compared as `day/month/year`.
- **Tree statistics**: node count, leaves and internal nodes.
- Performing a task marks it done in place; the performed and unperformed views are filtered in-order traversals.

## Run

```bash
gcc main.c -o tasks_bst && ./tasks_bst
```

Option **1** loads [`tasks.txt`](tasks.txt), which uses the format `id#name#date#duration-hours`.

---

*Data Structures (COMP2421), Birzeit University, Spring 2025.*
