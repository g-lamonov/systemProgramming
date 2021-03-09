#include <iostream>
using namespace std;
int main() {
    string str;
    cout << "Enter a string: " << endl;
    getline(cin, str);
    char *ptr_str = &str[0];
    char *end_str = &str[str.length()];
    int arr_size = str.length();
    int length[arr_size];
    int *l = &length[0];
    asm (
        "mov    %[l],       %%rbx           \n\t"
        "mov    %[ptr_str], %%rdx           \n\t"
        "mov    %[arr_size],%%rax           \n\t"

        "xor        %%rax,  %%rax           \n\t"
        "if:\n\t"
            "cmpb   $' ',   (%%rdx)         \n\t"
            "je else                        \n\t"
            "inc    %%rax                   \n\t"
            "add    $1,     %%rdx           \n\t"
            "cmp    %%rdx,  %[end_str]      \n\t"
            "je end_asm                     \n\t"
            "jmp if                         \n\t"
        "else:                              \n\t"
            "add    $1,     %[arr_size]     \n\t"
            "push   %%rax                   \n\t"
            "pop    (%%rbx)                 \n\t"
            "add    $4,     %%rbx           \n\t"
            "add    $1,     %%rdx           \n\t"
            "xor    %%rax,  %%rax           \n\t"
        "jmp if                             \n\t"

        "end_asm:                           \n\t"
            "add    $1,     %[arr_size]     \n\t"
            "push   %%rax                   \n\t"
            "pop    (%%rbx)                 \n\t"
            "add    $4,     %%rbx           \n\t"
            "add    $1,     %%rdx           \n\t"
            "xor    %%rax,  %%rax           \n\t"
        :
        :   [ptr_str]"m"(ptr_str),
            [end_str]"m"(end_str),
            [l]"m"(l),
            [arr_size]"m"(arr_size)
        :   "%rax", "%rbx", "%rdx"
    );
    arr_size -= str.length();
    cout << "Number of words: " << arr_size << endl;
    cout << "Length of words: ";
    for (int i = 0; i < arr_size; i++) {
        cout << length[i];
        if (i+1 < arr_size) {
            cout << ", ";} else {
            cout << "." <<endl;
        }
    }
    return 0;
}