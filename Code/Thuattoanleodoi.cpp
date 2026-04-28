#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

struct Canh {
    string dinh_ke;
//    int trong_so;
};

unordered_map<string, vector<Canh>> do_thi;

// Hàm dánh giá heuristic cho t?ng d?nh
unordered_map<string, int> ham_danh_gia;

bool la_muc_tieu(const string& dinh, const string& dich) {
    return dinh == dich;
}

void tim_kiem_leo_doi(string bat_dau, string dich) {
    vector<string> mo = {bat_dau};

    while (!mo.empty()) {
        string hien_tai = mo.front();
        mo.erase(mo.begin());

        cout << "Dang xet dinh: " << hien_tai << endl;

        if (la_muc_tieu(hien_tai, dich)) {
            cout << "Thanh cong: tim thay dinh dich!\n";
            return;
        }

        vector<string> ke_vi;
        for (auto& canh : do_thi[hien_tai]) {
            ke_vi.push_back(canh.dinh_ke);
        }

        // S?p x?p các k? v? theo giá tr? dánh giá tang d?n
        sort(ke_vi.begin(), ke_vi.end(), [](const string& a, const string& b) {
            return ham_danh_gia[a] < ham_danh_gia[b];
        });

        mo.insert(mo.begin(), ke_vi.begin(), ke_vi.end());
    }

    cout << "That bai: khong tim thay dinh dich.\n";
}
int main() {
    do_thi["A"] = {{"B"}, {"C"}, {"D"}};
    do_thi["B"] = {{"E"}};
    do_thi["C"] = {{"E"}, {"F"}};
    do_thi["D"] = {{"H"}};
    do_thi["E"] = {{"G"}};
    do_thi["F"] = {{"G"}};
    do_thi["G"] = {{"H"}};
    do_thi["H"] = {};

    // Kh?i t?o hàm dánh giá (giá tr? càng nh? càng g?n dích)
    ham_danh_gia["A"] = 30;
    ham_danh_gia["B"] = 20;
    ham_danh_gia["C"] = 10;
    ham_danh_gia["D"] = 25;
    ham_danh_gia["E"] = 13;
    ham_danh_gia["F"] = 15;
    ham_danh_gia["G"] = 18;
    ham_danh_gia["H"] = 0;

    // Ch?y thu?t toán
    tim_kiem_leo_doi("A", "H");

    return 0;
}
