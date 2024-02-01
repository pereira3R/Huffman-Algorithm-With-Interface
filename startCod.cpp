#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

struct Node {
    char data;
    unsigned freq;
    Node *left, *right;

    Node(char data, unsigned freq) {
        left = right = nullptr;
        this->data = data;
        this->freq = freq;
    }
};

struct compare {
    bool operator()(Node* l, Node* r) {
        return l->freq > r->freq;
    }
};

void printCodes(struct Node* root, string str, map<char, string>& huffmanCode) {
    if (!root) return;

    if (root->data != '$')
        huffmanCode[root->data] = str;

    printCodes(root->left, str + "0", huffmanCode);
    printCodes(root->right, str + "1", huffmanCode);
}

void HuffmanCodes(char data[], int freq[], int size, map<char, string>& huffmanCode) {
    struct Node *left, *right, *top;
    priority_queue<Node*, vector<Node*>, compare> minHeap;

    for (int i = 0; i < size; ++i)
        minHeap.push(new Node(data[i], freq[i]));

    while (minHeap.size() != 1) {
        left = minHeap.top();
        minHeap.pop();

        right = minHeap.top();
        minHeap.pop();

        top = new Node('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        minHeap.push(top);
    }

    printCodes(minHeap.top(), "", huffmanCode);
}

// Função para calcular a taxa de compressão
double calculateCompressionRate(map<char, string>& huffmanCode, int freq[], int size) {
    // Tamanho original (em bits) - cada caractere é 8 bits e assumimos 4,5GB de dados
    double originalSize = 4.5 * (2^30) * 8;
    double compressedSize = 0;

    for (int i = 0; i < size; i++) {
        compressedSize += huffmanCode.size() * freq[i];
    }

    // A taxa de compressão é a razão do tamanho original pelo tamanho comprimido
    return originalSize / compressedSize;
}

int main() {
    char arr[] = {'A', 'B', 'C', 'E', 'P', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    int freq[] = {2, 5, 1, 2, 1, 18, 13, 7, 12, 9, 6, 11, 7, 2, 4};
    int size = sizeof(arr) / sizeof(arr[0]);
    map<char, string> huffmanCode;

    HuffmanCodes(arr, freq, size, huffmanCode);

    cout << "Caractere\tCódigo de Huffman\n\n";
    for (auto pair: huffmanCode) {
        cout << pair.first << "\t\t" << pair.second << '\n';
    }

    double compressionRate = calculateCompressionRate(huffmanCode, freq, size);
    cout << "Taxa de compressão aproximadamente: " << compressionRate << endl;

    return 0;
}
