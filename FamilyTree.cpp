#include <iostream>
#include <string>
#include <queue>
#include <ctime>
#include <map>
#include <algorithm>
using namespace std;

struct DATE {
    int Day;
    int Month;
    int Year;
};

struct PERSON {
    string Name;
    string Gender;
    string BirthPlace;
    DATE Dob;
    DATE Dod;
    string Job;
};

struct NODE {
    PERSON Key;
    NODE* pLeft;
    NODE* pRight;
};

struct JobCount {
    string job;
    int count;

    JobCount(string j, int c) : job(j), count(c) {}
};

queue<PERSON> queueNode;

NODE* CreateNode(PERSON x);
void Init(NODE* &pRoot);
bool CheckDate(DATE date);
void InputPerson(PERSON &x);
NODE* SearchParentNode(NODE* pRoot, string Name);
bool IsMemberExist(NODE* pRoot, string Name);
int AddPerson(NODE* &pRoot, string ParentName, PERSON x);
int GetMax(int a, int b);
int GetHeight(NODE* pRoot);
void GetNodeByDepth(NODE* pRoot, int c, int d);
void PrintFamilyTree(NODE* pRoot);
int CountMembers(NODE* pRoot);
int CalculateAge(DATE dob, DATE dod);
void PrintPersonInfo(const PERSON &x);
NODE* FindPerson(NODE* pRoot, string Name, int &generation);
void FindAndPrintMember(NODE* pRoot, string Name);
int CalculateCurrentAge(DATE dob);
int TotalAgeOfLivingMember(NODE* pRoot);
void MemberWithoutChildren(NODE* pRoot);
void MemberAtGeneration(NODE* pRoot, int N);
void GetLivingMembers(NODE* pRoot, vector<PERSON> &livingMembers);
void PrintLivingMembersSorted(NODE* pRoot);
void CountMembersByGender(NODE* pRoot, int& maleCount, int& femaleCount);
void PrintLivingMembersSorted(NODE* pRoot);
void CountJobs(NODE* pRoot, map<string, int>& jobCount);
bool DeleteMember(NODE* &pRoot, string Name);
JobCount FindMostCommonJob(NODE* pRoot);

int main() {
    NODE* FamilyTree;
    Init(FamilyTree);

    int choice;
    do {
        cout << "-----------------------------" << endl;
        cout << "Menu:\n";
        cout << "1. Them thanh vien\n";
        cout << "2. In thong tin cua tat ca thanh vien\n";
        cout << "3. Tim va in thong tin cua mot thanh vien\n";
        cout << "4. Tinh tong tuoi cua cac thanh vien con song\n";
        cout << "5. In cac thanh vien chua co con\n";
        cout << "6. In cac thanh vien o doi thu N\n";
        cout << "7. In danh sach thanh vien con song va sap xep theo thu tu tu lon den nho\n";
        cout << "8. Thong ke cac thanh vien trong cay gia pha theo gioi tinh\n";
        cout << "9. Thong ke nghe nghiep cua cac thanh vien trong cay gia pha\n";
        cout << "10. Xoa bo mot thanh vien khoi cay gia pha\n";
        cout << "0. Thoat\n";
        cout << "Chon chuc nang: ";
        cin >> choice;
        cout << "-----------------------------" << endl;

        cin.ignore();

        switch (choice) {
            case 1: {
                // Thêm thành viên
                PERSON x;
                InputPerson(x);
                string ParentName;
                cout << "Nhap ten cha/me (neu khong co, nhap rong): ";
                getline(cin, ParentName);
                if (AddPerson(FamilyTree, ParentName, x)) 
                    cout << "Them thanh vien thanh cong\n";
                else 
                    cout << "Them thanh vien khong thanh cong\n";
                break;
            }
            case 2: {
                // In thông tin của tất cả thành viên
                cout << "Thong tin cua tat ca thanh vien:\n\n";
                if (FamilyTree == NULL) {
                    cout << "Khong co thanh vien nao trong gia pha.\n";
                } else {
                    PrintFamilyTree(FamilyTree);
                }
                break;
            }
            case 3: {
                // Tìm và in thông tin của một thành viên
                string name;
                cout << "Nhap ten thanh vien can tim: ";
                if (FamilyTree == NULL) {
                    cout << "\nKhong co thanh vien nao trong gia pha.\n";
                } else {
                    getline(cin, name);
                    FindAndPrintMember(FamilyTree, name);
                }
                break;
            }
            case 4: {
                // Tính tổng tuổi của các thành viên còn sống
                int TotalAge = TotalAgeOfLivingMember(FamilyTree);
                cout << "Tong so tuoi cua cac thanh vien con song: " << TotalAge << endl;
                break;
            }
            case 5: {
                // In các thành viên chưa có con
                cout << "Cac thanh vien chua co con:\n\n";
                if (FamilyTree == NULL) {
                    cout << "Khong co thanh vien nao trong gia pha.\n";
                } else {
                    MemberWithoutChildren(FamilyTree);
                }
                break;
            }
            case 6: {
                // In các thành viên ở đời thứ N
                int generation;
                if (FamilyTree == NULL) {
                    cout << "Khong co thanh vien nao trong gia pha.\n";
                } else {
                cout << "Nhap doi thu N can in: "; 
                cin >> generation;
                cout << "Cac thanh vien o doi thu " << generation << " la:\n\n";
                MemberAtGeneration(FamilyTree, generation);
                }
                break;
            }
            case 7: {
                // In danh sách thành viên còn sống và sắp xếp theo tuổi
                cout << "Danh sach thanh vien con song va sap xep theo thu tu tu lon den nho:\n\n";
                if (FamilyTree == NULL) {
                    cout << "Khong co thanh vien nao trong gia pha.\n";
                } else {
                PrintLivingMembersSorted(FamilyTree);
                }
                break;
            }
            case 8: {
                int maleCount = 0, femaleCount = 0;
                if (FamilyTree == NULL) {
                    cout << "Khong co thanh vien nao trong gia pha.\n";
                } else {
                CountMembersByGender(FamilyTree, maleCount, femaleCount);
                cout << "So luong thanh vien nam trong gia pha: " << maleCount << endl;
                cout << "So luong thanh vien nu trong gia pha: " << femaleCount << endl;
                }
                break;
            }
            case 9: {
                // Tìm nghề nghiệp có số lượng thành viên nhiều nhất
                JobCount mostCommonJob = FindMostCommonJob(FamilyTree);
                if (mostCommonJob.job.empty()) {
                cout << "Khong co thong tin nghe nghiep nao trong cay gia pha.\n";
                } else {
                cout << "Nghe nghiep co nhieu thanh vien nhat la: " << mostCommonJob.job << " voi " << mostCommonJob.count << " thanh vien.\n";
                }
                break;
            }
            case 10: {
                // Xóa thành viên
                string NameToDelete;
                if (FamilyTree == NULL) {
                    cout << "Khong co thanh vien nao trong gia pha.\n";
                } else {
                cout << "Nhap ten thanh vien can xoa: ";
                getline(cin, NameToDelete);
                
                if (DeleteMember(FamilyTree, NameToDelete)) {
                    cout << "Xoa thanh cong." << endl;
                } else {
                    cout << "Khong tim thay thanh vien." << endl;
                }
                }
                break;
            }
            case 0: {
                // Thoát chương trình
                cout << "Thoat chuong trinh\n";
                break;
            }
            default:
                cout << "Chuc nang khong hop le\n";
        }
    } while (choice != 0);

    return 0;
}

// Hàm tạo một nút mới với thông tin cá nhân x
NODE* CreateNode(PERSON x) {
    NODE* pNode = new NODE;
    pNode->Key = x;
    pNode->pLeft = pNode->pRight = NULL;
    return pNode;
}

// Hàm khởi tạo cây gia phả (cây rỗng)
void Init(NODE* &pRoot) {
    pRoot = NULL;
}

// Hàm kiểm tra tính hợp lệ của ngày tháng năm
bool CheckDate(DATE date) {
    if (date.Month < 1 || date.Month > 12) return false;
    if (date.Day < 1) return false;
    if (date.Year < 1) return false;

    int LastDayOfMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    
    bool YearLeap = (date.Year % 4 == 0 && date.Year % 100 != 0) || (date.Year % 400 == 0);
    if (YearLeap && date.Month == 2) {
        LastDayOfMonth[1] = 29;
    }

    if (date.Day > LastDayOfMonth[date.Month - 1]) return false;

    return true;
}

// Hàm nhập thông tin của một thành viên
void InputPerson(PERSON &x) {
    cout << "Ten: "; 
    getline(cin, x.Name);
    cout << "Gioi tinh: "; 
    getline(cin, x.Gender);
    cout << "Noi sinh: "; 
    getline(cin, x.BirthPlace);
    
    do {
        cout << "Ngay sinh (dd mm yyyy): ";
        cin >> x.Dob.Day >> x.Dob.Month >> x.Dob.Year;
        if (!CheckDate(x.Dob)) {
            cout << "Ngay sinh khong hop le. Vui long nhap lai." << endl;
        }
    } while (!CheckDate(x.Dob));

    do {
        cout << "Ngay mat (nhap 0 neu chua co ngay mat) (dd mm yyyy): ";
        cin >> x.Dod.Day >> x.Dod.Month >> x.Dod.Year;
        if (x.Dod.Year != 0 && !CheckDate(x.Dod)) {
            cout << "Ngay mat khong hop le. Vui long nhap lai." << endl;
        }
    } while (x.Dod.Year != 0 && !CheckDate(x.Dod));
    
    cin.ignore();
    
    cout << "Nghe nghiep: "; 
    getline(cin, x.Job);
}

// Hàm tìm nút cha của một thành viên trong cây
NODE* SearchParentNode(NODE* pRoot, string Name) {
    if (pRoot == NULL || pRoot->pLeft == NULL || pRoot->pRight == NULL) return NULL;
    
    queueNode.push(pRoot->Key);

    while (!queueNode.empty()) {
        PERSON temp;
        temp = queueNode.front();
        queueNode.pop();

        if (temp.Name == Name) return pRoot;

        if (pRoot->pLeft != NULL) queueNode.push(pRoot->pLeft->Key);
        if (pRoot->pRight != NULL) queueNode.push(pRoot->pRight->Key);
    }
    return NULL;
}

// Hàm kiểm tra thành viên đã tồn tại trong cây chưa
bool IsMemberExist(NODE* pRoot, string Name) {
    if (pRoot == NULL) return false;

    queueNode.push(pRoot->Key);
    
    while (!queueNode.empty()) {
        PERSON temp;
        temp = queueNode.front();
        queueNode.pop();

        if (temp.Name == Name) return true;

        if (pRoot->pLeft != NULL) queueNode.push(pRoot->pLeft->Key);
        if (pRoot->pRight != NULL) queueNode.push(pRoot->pRight->Key);
    }
    return false;
}

// Hàm thêm một thành viên mới vào cây gia phả
int AddPerson(NODE* &pRoot, string ParentName, PERSON x) {
    if (IsMemberExist(pRoot, ParentName) || ParentName.empty()) {
        if (pRoot == NULL) {
            pRoot = CreateNode(x);
            return 1;
        }

        if (pRoot->Key.Name == ParentName) {
            if (pRoot->pLeft == NULL) {
                pRoot->pLeft = CreateNode(x);
                return 1;
            } else {
                if (pRoot->pRight == NULL) {
                    pRoot->pRight = CreateNode(x);
                    return 1;
                }
            }
        }
        else {
            if (AddPerson(pRoot->pLeft, ParentName, x)) return 1;
            if (AddPerson(pRoot->pRight, ParentName, x)) return 1;
        }
    } 
    return 0;
}

// Hàm tính chiều cao của cây
int GetMax(int a, int b) {
    return a > b ? a : b;
}

// Hàm lấy chiều cao của cây
int GetHeight(NODE* pRoot) {
    if (pRoot == NULL) return 0;
    return 1 + GetMax(GetHeight(pRoot->pLeft), GetHeight(pRoot->pRight));
}

// Hàm lấy các nút ở độ sâu c và có độ sâu là d
void GetNodeByDepth(NODE* pRoot, int c, int d) {
    if (pRoot == NULL) return;
    if (c == d) cout << pRoot->Key.Name << "  ";
    else {
        GetNodeByDepth(pRoot->pLeft, c + 1, d);
        GetNodeByDepth(pRoot->pRight, c + 1, d);
    }
}

// Hàm in toàn bộ cây gia phả
void PrintFamilyTree(NODE* pRoot) {
    if (pRoot != NULL) {
        int age = CalculateAge(pRoot->Key.Dob, pRoot->Key.Dod);
        string status = (pRoot->Key.Dod.Year == 0) ? "Con song" : "Da mat";

        cout << "Ten: " << pRoot->Key.Name << endl;
        cout << "Gioi tinh: " << pRoot->Key.Gender << endl;
        cout << "Noi sinh: " << pRoot->Key.BirthPlace << endl;
        cout << "Tuoi: " << age << endl;
        cout << "Tinh trang: " << status << endl;
        cout << "Nghe nghiep: " << pRoot->Key.Job << endl;
        cout << "\n";

        PrintFamilyTree(pRoot->pLeft);
        PrintFamilyTree(pRoot->pRight);
    }
}

// Hàm đếm số lượng thành viên trong cây gia phả
int CountMembers(NODE* pRoot) {
    if (pRoot == NULL) return 0;
    return 1 + CountMembers(pRoot->pLeft) + CountMembers(pRoot->pRight);
}

// Hàm tính tuổi của một người dựa trên ngày sinh và ngày mất
int CalculateAge(DATE dob, DATE dod) {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int currentYear = 1900 + ltm->tm_year;
    int currentMonth = 1 + ltm->tm_mon;
    int currentDay = ltm->tm_mday;
    
    if (dod.Year != 0) return dod.Year - dob.Year - 1;
    else {
        if (currentMonth > dob.Month) return currentYear - dob.Year;
        else {
            if (currentDay > dob.Day) return currentYear - dob.Year;
            else return currentYear - dob.Year - 1;
        }
    }
}

// Hàm in thông tin của một người
void PrintPersonInfo(const PERSON &x) {
    int age = CalculateAge(x.Dob, x.Dod);
    string status = (x.Dod.Year == 0) ? "Con song" : "Da mat";

    cout << "Ho ten: " << x.Name << endl;
    cout << "Gioi tinh: " << x.Gender << endl;
    cout << "Noi sinh: " << x.BirthPlace << endl;
    cout << "Tuoi: " << age << endl;
    cout << "Tinh trang: " << status << endl;
    cout << "Nghe nghiep: " << x.Job << endl;
    cout << "\n";
}

// Hàm tìm một người trong cây theo tên và trả về nút chứa thông tin của người đó
NODE* FindPerson(NODE* pRoot, string Name, int &generation) {
    if (pRoot == NULL) return NULL;

    queueNode.push(pRoot->Key);
    
    while (!queueNode.empty()) {
        PERSON temp;
        temp = queueNode.front();
        queueNode.pop();

        if (temp.Name == Name) return pRoot;

        if (pRoot->pLeft != NULL) queueNode.push(pRoot->pLeft->Key);
        if (pRoot->pRight != NULL) queueNode.push(pRoot->pRight->Key);
    }
    return NULL;
}

// Hàm in thông tin của một người tìm được
void FindAndPrintMember(NODE* pRoot, string Name) {
    NODE* current = pRoot;
    while (current != NULL) {
        if (Name == current->Key.Name) {
            PrintPersonInfo(current->Key);
            return;
        } else if (Name < current->Key.Name) {
            current = current->pLeft;
        } else {
            current = current->pRight;
        }
    }
    cout << "Khong tim thay thanh vien co ten " << Name << " trong gia pha.\n";
}

// Hàm tính tổng số tuổi của các thành viên còn sống
int TotalAgeOfLivingMember(NODE* pRoot) {
    if (pRoot == NULL) return 0;

    int totalAge = 0;
    vector<PERSON> livingMembers;
    GetLivingMembers(pRoot, livingMembers);

    for (const auto& person : livingMembers) {
        totalAge += CalculateAge(person.Dob, person.Dod);
    }

    return totalAge;
}

// Hàm lấy danh sách các thành viên còn sống
void GetLivingMembers(NODE* pRoot, vector<PERSON> &livingMembers) {
    if (pRoot == NULL) return;

    if (pRoot->Key.Dod.Year == 0) {
        livingMembers.push_back(pRoot->Key);
    }

    GetLivingMembers(pRoot->pLeft, livingMembers);
    GetLivingMembers(pRoot->pRight, livingMembers);
}

// Hàm in các thành viên còn sống và sắp xếp theo tuổi
void PrintLivingMembersSorted(NODE* pRoot) {
    if (pRoot == NULL) return;

    vector<PERSON> livingMembers;
    GetLivingMembers(pRoot, livingMembers);

    sort(livingMembers.begin(), livingMembers.end(), [](const PERSON &a, const PERSON &b) {
        return CalculateAge(a.Dob, a.Dod) > CalculateAge(b.Dob, b.Dod);
    });

    for (const auto& person : livingMembers) {
        PrintPersonInfo(person);
    }
}

// Hàm tìm thành viên không có con
void MemberWithoutChildren(NODE* pRoot) {
    if (pRoot == NULL) return;

    if (pRoot->pLeft == NULL && pRoot->pRight == NULL) cout << pRoot->Key.Name << endl;

    MemberWithoutChildren(pRoot->pLeft);
    MemberWithoutChildren(pRoot->pRight);
}

// Hàm in các thành viên ở đời thứ N
void MemberAtGeneration(NODE* pRoot, int N) {
    if (pRoot == NULL) return;

    if (N == 1) {
        PrintPersonInfo(pRoot->Key);
        return;
    }

    MemberAtGeneration(pRoot->pLeft, N - 1);
    MemberAtGeneration(pRoot->pRight, N - 1);
}

// Hàm thống kê số lượng thành viên theo giới tính
void CountMembersByGender(NODE* pRoot, int& maleCount, int& femaleCount) {
    if (pRoot == NULL) return;

    // Kiểm tra giới tính của nút hiện tại
    if (pRoot->Key.Gender == "Nam") {
        maleCount++;
    } else if (pRoot->Key.Gender == "Nu") {
        femaleCount++;
    }

    // Đệ quy thống kê từ cây con trái và cây con phải
    CountMembersByGender(pRoot->pLeft, maleCount, femaleCount);
    CountMembersByGender(pRoot->pRight, maleCount, femaleCount);
}

// Hàm xóa một thành viên khỏi cây gia phả
bool DeleteMember(NODE* &pRoot, string Name) {
    if (pRoot == NULL) return false;

    if (pRoot->Key.Name == Name) {
        delete pRoot;
        pRoot = NULL;
        return true;
    }

    if (DeleteMember(pRoot->pLeft, Name) || DeleteMember(pRoot->pRight, Name)) {
        return true;
    }

    return false;
}

// Hàm đệ quy để thống kê số lượng các nghề nghiệp và lưu vào một map
void CountJobs(NODE* pRoot, map<string, int>& jobCount) {
    if (pRoot == NULL) return;

    // Tăng số lượng của nghề nghiệp hiện tại
    jobCount[pRoot->Key.Job]++;

    // Đệ quy với cây con trái và cây con phải
    CountJobs(pRoot->pLeft, jobCount);
    CountJobs(pRoot->pRight, jobCount);
}

// Hàm để tìm nghề nghiệp có số lượng thành viên nhiều nhất
JobCount FindMostCommonJob(NODE* pRoot) {
    map<string, int> jobCount;
    CountJobs(pRoot, jobCount);

    // Tìm nghề nghiệp có số lượng thành viên nhiều nhất trong map
    string mostCommonJob;
    int maxCount = 0;
    for (auto it = jobCount.begin(); it != jobCount.end(); ++it) {
        if (it->second > maxCount) {
            maxCount = it->second;
            mostCommonJob = it->first;
        }
    }

    return JobCount(mostCommonJob, maxCount);
}
