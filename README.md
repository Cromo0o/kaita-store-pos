# Kaita Store POS: Point of Sale and Inventory System

This project is a Point of Sale (POS) system developed in **C language**, designed to efficiently manage products and sales through a console interface. The system focuses on the practical application of sorting and searching algorithms, file management, and data persistence.

## Key Features

### 1. Inventory and Sales Management
* **Dynamic Loading:** Products are automatically loaded from an `inventario.csv` file upon system startup.
* **Stock Control:** Real-time validation of availability when adding products to the shopping cart.
* **Interactive Cart:** Users can add or remove products and view the current cart list before finalizing a sale.

### 2. Implemented Algorithms
To optimize performance and meet academic standards, the system utilizes the following algorithms:
* **Selection Sort:** Used to organize the inventory alphabetically by product name (A-Z) every time the list is updated or initialized.
* **Binary Search:** Implemented to efficiently verify product existence ($O(\log n)$) before adding new records to the catalog.

### 3. Data Persistence and Reporting
* **CSV File Integration:** All product information is synchronized with plain text files (`inventario.csv`), ensuring data is not lost when the program is closed.
* **Professional PDF Invoices:** Integration of the `pdfgen` library to export professional sales receipts including customer details, date, and tax breakdown (IVA).

### 4. Financial Management
* **Cashier Shift Report:** Provides a detailed summary at the end of the shift, including total sales with/without taxes and total revenue collected.
* **Configurable VAT (IVA):** Option to modify the tax percentage directly from the menu to comply with local regulations.

## Technical Specifications
* **Programming Language:** C.
* **External Libraries:** `pdfgen.h` and `pdfgen.c` for PDF generation.
* **Operating System:** Optimized for Windows (utilizes `windows.h` for colored console output and character encoding).
* **Architecture:** x86_64.

## 🛠️ Specifications
- **Programming Language**: C.
- **Compiler**: gcc or clang.
- **Architecture**: x86_64.
- **Project status**: In progress.
- **Operating system used**: Windows 11.

## 📚 Academic Details
- **University**: Escuela Politécnica Nacional
- **Subject**: Programming I.
- **Career**: Data Science and AI Engineering.
- **Developers**: Matthew Llerena Montoya, Kaya Alfusi.
