# AI Usage Log

**Project Title:** AI-Assisted Student Record and Result Management System  
**Course Code:** PRC1001 (Programming in C)  
**Program:** B. Tech Computer Science & Engineering (Semester I)  
**Student Name:** Ridhima Jalwi  
**SAP ID:** 590034676  
**University:** University of Petroleum and Energy Studies (UPES)  

---

## 1. Summary of AI Usage
In accordance with the project guidelines, AI tools (such as ChatGPT) were utilized solely as **learning and design assistants** during the development of this project. AI was consulted for conceptual brainstorming, category formulation for academic advising, generating representative edge-case test data, and optimizing documentation. All AI-suggested code snippets, logic models, and formulas were thoroughly examined, cross-verified with standard C specifications (C99), manually validated, and adapted to meet course constraints.

---

## 2. AI Interaction Log Table

| AI Tool | Prompt / Question Asked | How I Used / Verified the Response |
| :--- | :--- | :--- |
| **ChatGPT** | *"Suggest simple CGPA-based academic advice and suitable classification categories for undergraduate engineering students."* | **Idea & Logic:** AI proposed four tiers: *Excellent Performance* ($\ge 9.0$), *Good Performance* ($7.5 \le \text{CGPA} < 9.0$), *Needs Improvement* ($6.0 \le \text{CGPA} < 7.5$), and *Requires Immediate Attention* ($< 6.0$).<br>**Verification:** Adjusted thresholds to align with UPES 10-point grading scale. Transformed suggestions into C `if-else` branching logic in `getAIAdvice()`. |
| **ChatGPT** | *"How can I calculate cumulative GPA (CGPA) in C when different students have completed different numbers of semesters out of 8 semesters?"* | **Algorithm Design:** Suggested storing uncompleted semesters as `-1.0f` and averaging only non-negative entries ($count > 0$).<br>**Verification:** Implemented `calculateCGPA()` to iterate over 8 semesters, dynamically tallying completed semesters to prevent division-by-zero errors. |
| **ChatGPT** | *"Give test cases for a CGPA calculation function and yearly average calculation including students in Year 1 to 4."* | **Test Case Generation:** AI generated mock student profiles across all 4 years with diverse CGPAs.<br>**Verification:** Manually calculated the expected arithmetic means on paper (e.g., Year 1: $\frac{9.40 + 5.40}{2} = 7.40$) and confirmed that the program output matched exactly. |
| **ChatGPT** | *"How should I safely handle user string input in a C console application to avoid buffer overflow and newline issues from scanf?"* | **Code Safety:** Suggested using `fgets()` with trailing newline stripping (`\n`, `\r`) rather than unsafe `scanf("%s")` or `gets()`.<br>**Verification:** Created helper functions `readLine()`, `readInt()`, `readFloat()`, and `readLongLong()` to ensure robust, crash-free terminal input parsing. |
| **ChatGPT** | *"Explain how to sort student records in C both numerically by SAP ID and alphabetically by Name without losing the original database sequence."* | **Data Structure Protection:** AI recommended copying the array into a temporary buffer before applying sorting algorithms.<br>**Verification:** Implemented bubble sort algorithms with case-insensitive character comparison (`tolower()`) for names and integer comparison for SAP IDs. |

---

## 3. Reflection on Learning Outcomes from the AI Component

1. **Writing Clear and Context-Specific Prompts:**
   - Crafting precise prompts with explicit constraints (e.g., "in standard C99 without external libraries or dynamic memory") yields practical, actionable suggestions rather than complex or incompatible code.
2. **AI as an Idea and Logic Accelerator:**
   - AI effectively provided high-level category structures for the academic advisor and helped brainstorm encouraging, constructive feedback tailored to distinct student performance levels.
3. **Critical Verification vs. Blind Copying:**
   - AI outputs frequently contain platform-specific quirks (e.g., MSVCRT format string warnings like `%lld` in older compilers). By reviewing the generated logic, I replaced direct `scanf` calls with safe buffer-based parsing and ensured clean compilation under `gcc -Wall -Wextra -std=c99`.
4. **Translating Abstract Recommendations into C Code:**
   - Abstract qualitative advice was successfully mapped to quantitative mathematical ranges using structured `if-else` decision branches in C, creating a deterministic, transparent advisory engine.
