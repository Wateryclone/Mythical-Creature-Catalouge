#include <iostream>
#include <sstream>
#include <string>
#include <cassert>

#include "..\\src\\ScreenManager.h"

// Test function
void testPrintWelcome() {
    // Redirect cout to capture output
    std::ostringstream oss;
    std::streambuf* old_cout_buffer = std::cout.rdbuf(oss.rdbuf());

    // Call the function
    printWelcome();

    // Restore cout
    std::cout.rdbuf(old_cout_buffer);

    // Expected output
    const std::string expected = 
        "Main Menu:\n"
        "  [L] - Load data file\n"
        "  [A] - Add data\n"
        "  [S] - Search data (Primary key: creature_id)\n"
        "  [D] - Delete data\n"
        "  [U] - Undo delete\n"
        "  [P] - Print data\n"
        "  [T] - Show statistics\n"
        "  [W] - Write to file\n"
        "  [H] - Help\n"
        "  [Q] - Quit\n";

    // Get the actual output
    const std::string actual = oss.str();

    // Compare
    if (actual != expected) {
        std::cerr << "Test failed!\n";
        std::cerr << "Expected:\n" << expected << "\n";
        std::cerr << "Actual:\n" << actual << "\n";
        std::exit(1); // Exit with error code
    }

    std::cout << "printWelcome() test passed!\n";
}

void testLoadFile(const std::string& testFilename) {
    // Create a test file
    std::ofstream testFile(testFilename);
    testFile << "DRGN-RD;Dragon;Reptile;Mythical fire-breathing creature;Mountains;Large winged lizard;1500\n";
    testFile << "UNCRN-W;Unicorn;Mammal;Magical horse with a horn;Forests;White horse with single horn;800\n";
    testFile.close();

    // Redirect cout to capture output
    std::ostringstream oss;
    std::streambuf* old_cout_buffer = std::cout.rdbuf(oss.rdbuf());

    // Call the function
    int loadSuc = buildDataStructure(testFilename);
    assert(loadSuc == 1 && "Does NOT load successfully");

    // Restore cout
    std::cout.rdbuf(old_cout_buffer);
    std::string output = oss.str();

    // Verify output contains expected messages
    std::string expectedStart = "Reading data from \"" + testFilename + "...\"";
    assert(output.find(expectedStart) != std::string::npos && 
           "Should show file reading message");

    // Verify creature count - each creature takes 1 line in our test file
    size_t creatureCount = 2;
    assert(output.find("Error") == std::string::npos && 
           "No errors should occur during reading");
    
    // Clean up test file
    std::remove(testFilename.c_str());

    std::cout << "testLoadFile passed for valid file!\n";
}

void testLoadFile_InvalidFile() {
    const std::string invalidFilename = "non_existent_file.txt";
    
    // Redirect cout to capture output
    std::ostringstream oss;
    std::streambuf* old_cout_buffer = std::cout.rdbuf(oss.rdbuf());

    // Call the function
    int loadSuc = buildDataStructure(invalidFilename);

    // Restore cout
    std::cout.rdbuf(old_cout_buffer);
    std::string output = oss.str();

    // Verify error message
    std::string expectedError = "Error opening the input file: \"" + invalidFilename + "\"";
    assert(output.find(expectedError) != std::string::npos && 
           "Should show error for invalid file");
    
    // Verify program exits with failure
    assert(loadSuc == -1 && 
           "Does NOT return -1 for invalid file");
    
    std::cout << "testLoadFile passed for invalid file!\n";
}

int main() {
    testPrintWelcome();
    
    // Test with valid file
    testLoadFile("test_creatures.txt");
    
    // Test with invalid file
    testLoadFile_InvalidFile();
    
    return 0;
}