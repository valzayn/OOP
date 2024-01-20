#include <iostream>

struct Node
{
    int data;
    Node* next;
    Node* down;
    Node(int data_) : data(data_), next(nullptr), down(nullptr) {}
};

struct list
{
    Node* first;
    Node* last;

    list(): first(nullptr), last(nullptr) {}

    void addEl(int el, bool flag) {
        Node* nodel = new Node(el);
        if (first == nullptr) {
            first = nodel;
        }
        if (flag) {
            last->down = nodel;
        }
        else {
            if (last != nullptr) {
                last->next = nodel;
            }
        }
        last = nodel;
    }

    int Unic(Node* node, Node* list_s, int count_u) {
        Node* arrow = node;
        Node* arrow_l = list_s;
        if (node == nullptr) {
            return count_u;
        }
        else {
            while (arrow->next == nullptr && arrow->down != nullptr) {
                if ((arrow_l->data - arrow->data) < arrow->data) {
                    count_u++;
                }
                arrow_l = arrow_l->next;
                arrow = arrow->down;
            }
            if ((arrow_l->data - arrow->data) < arrow->data) {
                count_u++;
            }
            Unic(arrow->next, list_s, count_u);
        }
    }

    void SumStolb(Node* node, int *sum, int c) {
        Node* arrow = node;
        int count = 0;
        if (node == nullptr) {
            return;
        }
        else {
            while (arrow->down != nullptr) {
                if (count == c) {
                    *sum += arrow->data;
                }
                arrow = arrow->down;
                count++;
            }
            if (count = c) {
                *sum += arrow->data;
            }
            SumStolb(arrow->next, sum, c);
        }
    }
    void print(Node* node) {
        Node* arrow = node;
        if (node == nullptr) {
            return;
        }
        else {
            while (arrow->next == nullptr && arrow->down != nullptr) {
                std::cout << arrow->data << " ";
                arrow = arrow->down;
            }
            std::cout << arrow->data << " ";
            std::cout << "\n";
            print(arrow->next);
            std::cout << "\n";
        }
    }
};


int main()
{
    list l, sum_l;
    Node* arrow;
    int n, m, a, s, c;
    bool k = false;
    std::cout << "Enter n, m: ";
    std::cin >> n >> m;
    for (int i = 0; i < n; i++) {
        std::cin >> a;
        l.addEl(a, k);
        k = true;
        for (int j = 1; j < m; j++) {
            std::cin >> a;
            l.addEl(a, k);
        }
        k = false;
    }
    c = 0;
    s = 0;
    arrow = l.first;
    for (int i = 0; i < n; i++) {
        l.SumStolb(arrow, &s, i);
        sum_l.addEl(s, 0);
        s = 0;
    }
    arrow = sum_l.first->next;
    for (int i = 0; i < n - 2; i++) {
        arrow->data -= sum_l.last->data;
        arrow = arrow->next;
    }
    c = l.Unic(l.first, sum_l.first, 0);
    std::cout << c << "\n";
    std::cout << "\n";

}
