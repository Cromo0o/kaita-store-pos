<div align="center">

# 🛒 Kaita Store POS
### Point of Sale and Inventory System

![Language](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Platform](https://img.shields.io/badge/Platform-Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)
![Status](https://img.shields.io/badge/Status-Beta-orange?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

<p align="center">
  <b>An efficient Point of Sale system developed in C, focused on sorting, searching, and data persistence algorithms.</b>
</p>

</div>

---

## 🚀 Key Features

### 1. 📦 Inventory and Sales Management
* **Dynamic Loading:** Products are automatically loaded from an `inventario.csv` file upon system startup.
* **Stock Control:** Real-time validation of availability when adding products to the shopping cart.
* **Interactive Cart:** Users can add or remove products and view the current cart list before finalizing a sale.

### 2. ⚡ Implemented Algorithms
To optimize performance and meet academic standards, the system utilizes:

| Algorithm | Functionality | Complexity |
| :--- | :--- | :---: |
| **Selection Sort** | Used to organize the inventory alphabetically (A-Z) on updates. | $O(n^2)$ |
| **Binary Search** | Efficiently verifies product existence before adding new records. | $O(\log n)$ |

### 3. 💾 Data Persistence & Reporting
* **CSV Integration:** Full synchronization with `inventario.csv` to prevent data loss.
* **PDF Invoices:** Uses `pdfgen` to export professional receipts with customer details and taxes.

### 4. 💰 Financial Management
* **Shift Report:** Detailed summary of total sales and revenue.
* **Configurable IVA:** Modify tax percentages directly from the menu.

---

## 🛠️ Technical Specifications

<div align="center">

| Component | Detail |
| :--- | :--- |
| **Language** | C (Standard C99/C11) |
| **Compiler** | GCC or Clang |
| **Libraries** | `pdfgen.h`, `windows.h` (Console UI) |
| **OS** | Windows 10/11 |
| **Architecture** | x86_64 |

</div>

---

## 📚 Academic Details

> **Institution:** Escuela Politécnica Nacional (EPN)  
> **Subject:** Programming I  
> **Career:** Data Science and AI Engineering

### 👥 Developers

<table align="center">
  <tr>
    <td align="center"><b>Matthew Llerena Montoya</b></td>
    <td align="center"><b>Kaya Alfusi Duque</b></td>
  </tr>
</table>

---
<div align="center">
    <sub>Developed for the final semester project - 2025/2026</sub>
</div>
