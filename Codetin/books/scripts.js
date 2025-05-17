// Content for each section
const sections = {
    section1: {
      title: 'Introduction to C++',
      content: `
        <p>C++ is a powerful general-purpose programming language. It is widely used for systems software, game development, and performance-critical applications.</p>
        <h2>Code Example:</h2>
        <pre><code class="language-cpp">
  // Simple C++ Program
  #include &lt;iostream&gt;
  using namespace std;
  
  int main() {
      cout << "Hello, world!" << endl;
      return 0;
  }
        </code></pre>
      `
    },
    section2: {
      title: 'Basic Syntax',
      content: `
        <p>The basic syntax of C++ includes declarations, operators, loops, and more. Below is an example showing a basic loop:</p>
        <h2>Code Example:</h2>
        <pre><code class="language-cpp">
  // C++ Code with loops
  #include &lt;iostream&gt;
  using namespace std;
  
  int main() {
      for (int i = 0; i < 5; i++) {
          cout << "Iteration: " << i << endl;
      }
      return 0;
  }
        </code></pre>
      `
    },
    section3: {
      title: 'Advanced Topics',
      content: `
        <p>C++ offers advanced features such as templates, pointers, and the Standard Template Library (STL). These are key for mastering the language.</p>
        <h2>Code Example:</h2>
        <pre><code class="language-cpp">
  // C++ Template Function
  template<typename T>
  T add(T a, T b) {
      return a + b;
  }
  
  int main() {
      cout << add(5, 3) << endl; // Output: 8
  }
        </code></pre>
      `
    }
  };
  
  // Function to load the appropriate section
  function loadSection(section) {
    // Get the content and title for the selected section
    const sectionData = sections[section];
    
    // Update the content area with the section's title and content
    const contentDiv = document.getElementById('content');
    contentDiv.innerHTML = `
      <h1>${sectionData.title}</h1>
      ${sectionData.content}
      <footer>
        <a href="#" onclick="loadSection('index')">Back to Table of Contents</a>
      </footer>
    `;
  }
  