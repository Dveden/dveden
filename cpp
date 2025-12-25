#include <iostream>
#include <string>
#include <locale>
#include <unordered_set>

using namespace std;

class TextState {
    private:
        int glas, soglas, words;
        
        const unordered_set<string> letters = {"а","б","в","г","д","е","ё","ж","з","и","й","к","л","м","н",
        "о","п","р","с","т","у","ф","х","ц","ч","ш","щ","ъ","ы","ь","э","ю","я",
        "А","Б","В","Г","Д","Е","Ё","Ж","З","И","Й","К","Л","М","Н",
        "О","П","Р","С","Т","У","Ф","Х","Ц","Ч","Ш","Щ","Ъ","Ы","Ь","Э","Ю","Я",
        "a","b","c","d","e","f","g","h","i","j","k","l","m","n",
        "o","p","q","r","s","t","u","v","w","x","y","z",
        "A","B","C","D","E","F","G","H","I","J","K","L","M","N",
        "O","P","Q","R","S","T","U","V","W","X","Y","Z"
            
        };
        const unordered_set<string> glasset ={  "а","е","ё","и","о","у","ы","э","ю","я",
        "А","Е","Ё","И","О","У","Ы","Э","Ю","Я",
        "a","e","i","o","u","A","E","I","O","U"
            
        };
        string getChar(const string& s, size_t& pos) const {
            if (pos >= s.length()) return "";
            unsigned char c = s[pos];
            int len = 1;
            if (c >= 0xC2 && c <= 0xDF && pos + 1 < s.length()) len = 2;
            else if (c >= 0xE0 && c <= 0xEF && pos + 2 < s.length()) len = 3;
            else if (c >= 0xF0 && c <= 0xF4 && pos + 3 < s.length()) len = 4;
            string result = s.substr(pos, len);
            pos += len - 1;
            return result;
        }
    public:
    TextState(const string& text) : glas(0), soglas(0), words(0) {
        bool inword = false;
        for (size_t i = 0; i < text.length(); i++){
            string ch = getChar(text, i);
            if (letters.count(ch)) {
                if (glasset.count(ch)) glas++;
                else soglas++;
                if (!inword) {
                    inword = true;
                    words++;
                }
            } else {
                    inword = false;}
        }
    }
    int getglas() const { return glas; }
    int getsoglas() const { return soglas; }
    int getwords() const { return words; }
};
int main() {
    setlocale(LC_ALL, "en_US.UTF-8");
    cout << "Введите строку: ";
    string input;
    getline(cin, input);
    TextState stats(input);
    cout << "глас " << stats.getglas() << endl;
    cout << "согл " << stats.getsoglas() << endl;
    cout << "слова " << stats.getwords() << endl;
    return 0;
}
