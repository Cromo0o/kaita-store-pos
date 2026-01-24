<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Kaita Store POS - Documentation</title>
    <style>
        :root {
            --primary-color: #2563eb;
            --secondary-color: #1e293b;
            --bg-color: #f8fafc;
            --card-bg: #ffffff;
            --text-color: #334155;
            --accent-color: #eff6ff;
            --border-radius: 8px;
        }

        body {
            font-family: 'Segoe UI', system-ui, -apple-system, sans-serif;
            line-height: 1.6;
            color: var(--text-color);
            background-color: var(--bg-color);
            margin: 0;
            padding: 20px;
        }

        .container {
            max-width: 900px;
            margin: 0 auto;
            background-color: var(--card-bg);
            padding: 40px;
            border-radius: var(--border-radius);
            box-shadow: 0 4px 6px -1px rgba(0, 0, 0, 0.1), 0 2px 4px -1px rgba(0, 0, 0, 0.06);
        }

        h1 {
            color: var(--secondary-color);
            font-size: 2.25rem;
            margin-bottom: 1.5rem;
            border-bottom: 2px solid var(--primary-color);
            padding-bottom: 10px;
        }

        h2 {
            color: var(--secondary-color);
            font-size: 1.5rem;
            margin-top: 2rem;
            margin-bottom: 1rem;
            display: flex;
            align-items: center;
        }

        h3 {
            color: var(--primary-color);
            font-size: 1.25rem;
            margin-top: 1.5rem;
        }

        p {
            margin-bottom: 1rem;
        }

        ul {
            list-style-type: none;
            padding-left: 0;
        }

        li {
            margin-bottom: 0.5rem;
            padding-left: 1.5rem;
            position: relative;
        }

        li::before {
            content: "•";
            color: var(--primary-color);
            font-weight: bold;
            position: absolute;
            left: 0;
            width: 1rem;
            display: inline-block;
        }

        code {
            font-family: 'Consolas', 'Monaco', 'Courier New', monospace;
            background-color: var(--accent-color);
            color: var(--primary-color);
            padding: 0.2em 0.4em;
            border-radius: 4px;
            font-size: 0.9em;
        }

        .highlight-box {
            background-color: var(--accent-color);
            border-left: 4px solid var(--primary-color);
            padding: 15px;
            margin: 20px 0;
            border-radius: 0 var(--border-radius) var(--border-radius) 0;
        }

        .academic-info {
            background-color: var(--secondary-color);
            color: white;
            padding: 20px;
            border-radius: var(--border-radius);
            margin-top: 30px;
        }
        
        .academic-info h2, .academic-info li::before {
            color: #60a5fa; /* Lighter blue for dark background */
        }
        
        .footer {
            text-align: center;
            font-size: 0.85rem;
            color: #94a3b8;
            margin-top: 40px;
            padding-top: 20px;
            border-top: 1px solid #e2e8f0;
        }

        @media (max-width: 600px) {
            .container {
                padding: 20px;
            }
            h1 {
                font-size: 1.75rem;
            }
        }
    </style>
</head>
<body>

    <div class="container">
        <h1>Kaita Store POS: Point of Sale and Inventory System</h1>
        
        <p>This project is a Point of Sale (POS) system developed in <strong>C language</strong>, designed to efficiently manage products and sales through a console interface. The system focuses on the practical application of sorting and searching algorithms, file management, and data persistence.</p>

        <h2>Key Features</h2>

        <div class="highlight-box">
            <h3>1. Inventory and Sales Management</h3>
            <ul>
                <li><strong>Dynamic Loading:</strong> Products are automatically loaded from an <code>inventario.csv</code> file upon system startup.</li>
                <li><strong>Stock Control:</strong> Real-time validation of availability when adding products to the shopping cart.</li>
                <li><strong>Interactive Cart:</strong> Users can add or remove products and view the current cart list before finalizing a sale.</li>
            </ul>

            <h3>2. Implemented Algorithms</h3>
            <p>To optimize performance and meet academic standards, the system utilizes the following algorithms:</p>
            <ul>
                <li><strong>Selection Sort:</strong> Used to organize the inventory alphabetically by product name (A-Z) every time the list is updated or initialized.</li>
                <li><strong>Binary Search:</strong> Implemented to efficiently verify product existence (<code>O(log n)</code>) before adding new records to the catalog.</li>
            </ul>

            <h3>3. Data Persistence and Reporting</h3>
            <ul>
                <li><strong>CSV File Integration:</strong> All product information is synchronized with plain text files (<code>inventario.csv</code>), ensuring data is not lost when the program is closed.</li>
                <li><strong>Professional PDF Invoices:</strong> Integration of the <code>pdfgen</code> library to export professional sales receipts including customer details, date, and tax breakdown (IVA).</li>
            </ul>

            <h3>4. Financial Management</h3>
            <ul>
                <li><strong>Cashier Shift Report:</strong> Provides a detailed summary at the end of the shift, including total sales with/without taxes and total revenue collected.</li>
                <li><strong>Configurable VAT (IVA):</strong> Option to modify the tax percentage directly from the menu to comply with local regulations.</li>
            </ul>
        </div>

        <h2>Technical Specifications</h2>
        <ul>
            <li><strong>Programming Language:</strong> C.</li>
            <li><strong>External Libraries:</strong> <code>pdfgen.h</code> and <code>pdfgen.c</code> for PDF generation.</li>
            <li><strong>Operating System:</strong> Optimized for Windows (utilizes <code>windows.h</code> for colored console output and character encoding).</li>
            <li><strong>Architecture:</strong> x86_64.</li>
        </ul>

        <h2>🛠️ Specifications</h2>
        <ul>
            <li><strong>Programming Language:</strong> C.</li>
            <li><strong>Compiler:</strong> gcc or clang.</li>
            <li><strong>Architecture:</strong> x86_64.</li>
            <li><strong>Project status:</strong> In progress.</li>
            <li><strong>Operating system used:</strong> Windows 11.</li>
        </ul>

        <div class="academic-info">
            <h2>📚 Academic Details</h2>
            <ul>
                <li><strong>University:</strong> Escuela Politécnica Nacional</li>
                <li><strong>Subject:</strong> Programming I.</li>
                <li><strong>Career:</strong> Data Science and AI Engineering.</li>
                <li><strong>Developers:</strong> Matthew Llerena Montoya, Kaya Alfusi.</li>
            </ul>
        </div>

        <div class="footer">
            Generated from README.md | Kaita Store POS
        </div>
    </div>

</body>
</html>
