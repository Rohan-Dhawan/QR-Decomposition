# QR Decomposition using Householder Transformations

This project implements the **QR Decomposition** of a matrix using **Householder transformations** in C++. It was developed as part of the *Computer Language for Engineers* course (Winter Semester 2023-2024).

---

## 📚 Description

**QR Decomposition** is a way to factorize a matrix A into the product of two matrices, Q and R, where Q is an orthogonal matrix (its columns are orthonormal vectors) and R is an upper triangular matrix, used to:
- Solve linear systems and least square approximation problems
- Compute eigenvalues and eigenvectors
- Improve numerical stability for ill-conditioned matrices

This implementation uses **Householder transformations** to perform the decomposition:
- `A = Q · R`, where:
  - `Q` is an orthogonal matrix
  - `R` is an upper triangular matrix
The basic idea behind Householder transformations is to successively zero out elements below the main diagonal of a matrix by multiplying it on the left by a series of orthogonal matrices.
The Householder matrix is defined as:

𝐻=𝐼−2𝑣𝑣ᵀ
---

## 🧠 Key Features

- Handles square and non-square matrices
- Uses Householder reflections to zero out subdiagonal elements
- Outputs intermediate steps and final `Q` and `R` matrices
- Log files and iterations are provided for analysis

---

## 🗂 Project Structure

```
├── src/
│   ├── Base.cpp               # Basic operations and helper functions
│   └── Qr_decomposition.cpp   # Core QR decomposition logic
│
├── include/
│   ├── Base.h                 # Declarations for base functions
│   └── QR_decompo.h           # Declarations for QR decomposition
│
├── main.cpp                   # Entry point of the program
├── README.md                  # Project overview
└── .gitignore                 # Excludes binary and temporary files
```

---

## 🛠 How to Compile

Use `g++` to compile the project:

```bash
g++ -Iinclude src/*.cpp main.cpp -o qr_decomposition
```

Then run the program:

```bash
./qr_decomposition
```

---

## 📊 Example Outputs

- For a 3x3 matrix:
  - Displays the updated `Q` and `R` matrices after each transformation
- For a 4x4 or non-square matrix:
  - Adjusts dimensions accordingly and logs the process

---

## 🔍 Applications

- Solving overdetermined systems (least squares)
- Signal processing
- Simulation and modeling
- Eigenvalue computations

---

## 📄 License

This project is for academic and educational purposes.

---