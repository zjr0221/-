#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <set>
#include <algorithm>
#include <iomanip>
using namespace std;


// 文物信息类
class Artifact {
private:
	int id;                  // 序号
	string name;             // 文物名称
	string year;             // 文物年代
	string status;            // 展出状态
	int exhibitionCount;       // 展出次数
	time_t exhibitionDuration; // 展出时长

public:
	Artifact() {}
	int getExhibitionCount() {
		return this->exhibitionCount;
	}//vector动态数组可以存放任意类型 static静态成员函数
	static void printArtifact(const vector<Artifact>& artifacts);// 查看全部文物
	static void modifyArtifact(vector<Artifact>& artifacts);// 修改文物信息
	static void modifyArtifactByStatus(vector<Artifact>& artifacts);// 根据展出状态修改文物信息
	static void addArtifact(vector<Artifact>& artifacts);// 增加文物
	static void searchArtifact(vector<Artifact>& artifacts);// 查询文物
	static void  sortArtifact(vector<Artifact>& artifacts);// 根据展出次数对文物进行排序
	static void  caclArtifact(vector<Artifact>& artifacts);// 根据展出时长计算文物护理时长,并展示7天后可展出的文物
	static time_t CalculateCareDuration(time_t exhibitionDuration);


};


/**
 * 添加文物信息
*/
void Artifact::addArtifact(vector<Artifact>& artifacts) {//接受vector类型的引用artifacts来存储
	cout << "输入新的文物信息：" << endl;
	Artifact artifact;
	while (true) {
		cout << "请输入序号:";
		cin >> artifact.id;
		bool flag = true;
		if (artifact.id >= 1 && artifact.id <= 9999) {
			for (auto it = artifacts.begin(); it != artifacts.end(); ++it) {//内部循环遍历 artifacts 列表，检查是否有与输入的序号相同的文物对象。
				if (it->id == artifact.id) {
					flag = false;
				}
			}
			if (flag) {
				break;
			}
			else {
				cout << "该序号已存在,请重新输入!" << endl;
			}
		}
		else {
			cout << "序号需在1~9999之间,请重新输入!" << endl;
		}
	}
	cout << "请输入文物名称:";
	cin >> artifact.name;
	cout << "请输入文物年代:";
	cin >> artifact.year;
	cout << "请输入展出状态(是/否):";
	cin >> artifact.status;
	cout << "请输入展出次数:";
	cin >> artifact.exhibitionCount;
	cout << "请输入展出时长:";
	cin >> artifact.exhibitionDuration;

	artifacts.push_back(artifact);//将新创建的artifact对象添加到artifacts向量的末尾
	cout << "添加成功！" << endl;
}


/**
 * 修改文物信息
*/
void Artifact::modifyArtifact(vector<Artifact>& artifacts) {
	int id;
	cout << "请输入要修改的文物信息序号:";
	cin >> id;
	for (auto& artifact : artifacts) {//获取artifacs中元素的引用并修改
		if (artifact.id == id) {
			cout << "请输入新的文物名称:";
			cin >> artifact.name;
			cout << "请输入新的文物年代:";
			cin >> artifact.year;
			cout << "请输入新的展出状态(是/否):";
			cin >> artifact.status;
			cout << "请输入新的展出次数:";
			cin >> artifact.exhibitionCount;
			cout << "请输入新的展出时长:";
			cin >> artifact.exhibitionDuration;

			cout << "修改成功！" << endl;
			return;
		}
	}
	cout << "未找到该序号的文物信息！" << endl;

}


/**
 * 修改文物信息展出状态
*/
void Artifact::modifyArtifactByStatus(vector<Artifact>& artifacts) {
	int id;
	cout << "请输入要修改的文物信息序号:";
	cin >> id;
	for (auto& artifact : artifacts) {//获取artifacs中元素的引用并修改
		if (artifact.id == id) {
			cout << "请输入新的展出状态(是/否):";
			cin >> artifact.status;
			cout << "修改成功！" << endl;
			return;
		}
	}
	cout << "未找到该序号的文物信息！" << endl;
}

/**
 * 查询文物信息
*/
void Artifact::searchArtifact(vector<Artifact>& artifacts) {
	int id;
	cout << "请输入要查询的文物信息序号:";
	cin >> id;
	for (auto it = artifacts.begin(); it != artifacts.end(); ++it) {
		if (it->id == id) {
			cout << "序号:" << it->id << ",文物名称:" << it->name << ",文物年代:" << it->year << ",展出状态:" << it->status <<
				",展出次数:" << it->exhibitionCount << ",展出时长:" << it->exhibitionDuration / 86400 << "天" << 
				endl;
			return;
		}
	}

}

// 快速排序的分区函数
static int partition(vector<Artifact>& artifacts, int low, int high) {
	Artifact pivot = artifacts[high]; // 选择最后一个元素作为基准值
	int i = (low - 1); // 小于基准值的元素的索引

	for (int j = low; j <= high - 1; j++) {
		// 如果当前元素大于或等于基准值，则跳过
		if (artifacts[j].getExhibitionCount() >= pivot.getExhibitionCount()) {
			i++; // 增加索引i
			std::swap(artifacts[i], artifacts[j]);
		}
	}
	std::swap(artifacts[i + 1], artifacts[high]); // 将基准值放到正确的位置
	return (i + 1);
}

// 快速排序的递归函数
static void quickSort(vector<Artifact>& artifacts, int low, int high) {
	if (low < high) {
		int pi = partition(artifacts, low, high);

		// 递归地对基准值两边的子数组进行排序
		quickSort(artifacts, low, pi - 1);
		quickSort(artifacts, pi + 1, high);
	}
}

/**
 * 根据展出次数对文物进行排序
*/
void Artifact::sortArtifact(vector<Artifact>& artifacts) {
	int n = artifacts.size();//获取 artifacts向量中元素的数量
	quickSort(artifacts, 0, n - 1); // 从第一个元素到最后一个元素进行排序
	Artifact::printArtifact(artifacts);// 打印排序后的文物信息
}


/**
 * 查看全部文物信息
*/
void Artifact::printArtifact(const vector<Artifact>& artifacts) {
	if (artifacts.empty()) {
		cout << "记录为空！" << endl;
		return;
	}
	for (const auto& artifact : artifacts) {
		cout << "序号:" << artifact.id << ",文物名称:" << artifact.name << ",文物年代:" << artifact.year <<
			",展出状态:" << artifact.status << ",展出次数:" << artifact.exhibitionCount <<
			",展出时长:" << artifact.exhibitionDuration / 86400 << "天"
			<< endl;
	}

}

// 计算护理时长
time_t Artifact::CalculateCareDuration(time_t exhibitionDuration) {
	// 设护理时长是展出时长的10%
	return exhibitionDuration / 10;
}

/**
 * 展示7天后可展出的文物
*/
void Artifact::caclArtifact(vector<Artifact>& artifacts) {
	time_t currentTime = time(nullptr);// currentTime变量获取当前的时间
	cout << "7天后可展出的文物信息为:" << endl;
	for (const auto& artifact : artifacts) {
		time_t careDuration = Artifact::CalculateCareDuration(artifact.exhibitionDuration);//通过调用CalculateCareDuration计算得到护理时长。
		time_t nextAvailableTime = artifact.exhibitionDuration + careDuration;//文物下次可以展出的时间：文物当前展出时长+护理时长
		if (nextAvailableTime <= currentTime + 7 * 24 * 60 * 60) {
			cout << "序号:" << artifact.id << ",文物名称:" << artifact.name << ",文物年代:" << artifact.year <<
				",展出状态:" << artifact.status << ",展出次数:" << artifact.exhibitionCount <<
				",展出时长:" << artifact.exhibitionDuration / 86400<< "天" <<
				 endl;
		}
	}
}


/**
 * 主函数
*/
int main() {
	vector<Artifact> artifacts;//定义了名为 artifacts 的向量，用于存储 Artifact 类型的对象
	int choice;//储存用户输入的选择
	while (true) {
		cout << "===============文物信息管理系统==================" << endl;
		cout << "*********1.查看全部文物信息**********" << endl;
		cout << "*********2.修改文物信息**************" << endl;
		cout << "*********3.修改文物展出状态**********" << endl;
		cout << "*********4.根据展出次数排序文物信息**" << endl;
		cout << "*********5.查询文物信息**************" << endl;
		cout << "*********6.添加文物信息**************" << endl;
		cout << "*********7.展示7天后可展出文物信息***" << endl;
		cout << "*********0.退出程序******************" << endl;
		cout << "请选择:";
		cin >> choice;
		switch (choice) {
		case 0:
			cout << "系统已退出,欢迎下次使用!" << endl;
			return 0;
		case 1:
			Artifact::printArtifact(artifacts);
			break;
		case 2:
			Artifact::modifyArtifact(artifacts);
			break;
		case 3:
			Artifact::modifyArtifactByStatus(artifacts);
			break;
		case 4:
			Artifact::sortArtifact(artifacts);
			break;
		case 5:
			Artifact::searchArtifact(artifacts);
			break;
		case 6:
			Artifact::addArtifact(artifacts);
			break;
		case 7:
			Artifact::caclArtifact(artifacts);
			break;
		default:
			cout << "无效输入！" << endl;
			break;
		}
	}
	return 0;
}