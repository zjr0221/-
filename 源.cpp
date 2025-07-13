#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <set>
#include <algorithm>
#include <iomanip>
using namespace std;


// ������Ϣ��
class Artifact {
private:
	int id;                  // ���
	string name;             // ��������
	string year;             // �������
	string status;            // չ��״̬
	int exhibitionCount;       // չ������
	time_t exhibitionDuration; // չ��ʱ��

public:
	Artifact() {}
	int getExhibitionCount() {
		return this->exhibitionCount;
	}//vector��̬������Դ���������� static��̬��Ա����
	static void printArtifact(const vector<Artifact>& artifacts);// �鿴ȫ������
	static void modifyArtifact(vector<Artifact>& artifacts);// �޸�������Ϣ
	static void modifyArtifactByStatus(vector<Artifact>& artifacts);// ����չ��״̬�޸�������Ϣ
	static void addArtifact(vector<Artifact>& artifacts);// ��������
	static void searchArtifact(vector<Artifact>& artifacts);// ��ѯ����
	static void  sortArtifact(vector<Artifact>& artifacts);// ����չ�������������������
	static void  caclArtifact(vector<Artifact>& artifacts);// ����չ��ʱ���������ﻤ��ʱ��,��չʾ7����չ��������
	static time_t CalculateCareDuration(time_t exhibitionDuration);


};


/**
 * ���������Ϣ
*/
void Artifact::addArtifact(vector<Artifact>& artifacts) {//����vector���͵�����artifacts���洢
	cout << "�����µ�������Ϣ��" << endl;
	Artifact artifact;
	while (true) {
		cout << "���������:";
		cin >> artifact.id;
		bool flag = true;
		if (artifact.id >= 1 && artifact.id <= 9999) {
			for (auto it = artifacts.begin(); it != artifacts.end(); ++it) {//�ڲ�ѭ������ artifacts �б�����Ƿ���������������ͬ���������
				if (it->id == artifact.id) {
					flag = false;
				}
			}
			if (flag) {
				break;
			}
			else {
				cout << "������Ѵ���,����������!" << endl;
			}
		}
		else {
			cout << "�������1~9999֮��,����������!" << endl;
		}
	}
	cout << "��������������:";
	cin >> artifact.name;
	cout << "�������������:";
	cin >> artifact.year;
	cout << "������չ��״̬(��/��):";
	cin >> artifact.status;
	cout << "������չ������:";
	cin >> artifact.exhibitionCount;
	cout << "������չ��ʱ��:";
	cin >> artifact.exhibitionDuration;

	artifacts.push_back(artifact);//���´�����artifact������ӵ�artifacts������ĩβ
	cout << "��ӳɹ���" << endl;
}


/**
 * �޸�������Ϣ
*/
void Artifact::modifyArtifact(vector<Artifact>& artifacts) {
	int id;
	cout << "������Ҫ�޸ĵ�������Ϣ���:";
	cin >> id;
	for (auto& artifact : artifacts) {//��ȡartifacs��Ԫ�ص����ò��޸�
		if (artifact.id == id) {
			cout << "�������µ���������:";
			cin >> artifact.name;
			cout << "�������µ��������:";
			cin >> artifact.year;
			cout << "�������µ�չ��״̬(��/��):";
			cin >> artifact.status;
			cout << "�������µ�չ������:";
			cin >> artifact.exhibitionCount;
			cout << "�������µ�չ��ʱ��:";
			cin >> artifact.exhibitionDuration;

			cout << "�޸ĳɹ���" << endl;
			return;
		}
	}
	cout << "δ�ҵ�����ŵ�������Ϣ��" << endl;

}


/**
 * �޸�������Ϣչ��״̬
*/
void Artifact::modifyArtifactByStatus(vector<Artifact>& artifacts) {
	int id;
	cout << "������Ҫ�޸ĵ�������Ϣ���:";
	cin >> id;
	for (auto& artifact : artifacts) {//��ȡartifacs��Ԫ�ص����ò��޸�
		if (artifact.id == id) {
			cout << "�������µ�չ��״̬(��/��):";
			cin >> artifact.status;
			cout << "�޸ĳɹ���" << endl;
			return;
		}
	}
	cout << "δ�ҵ�����ŵ�������Ϣ��" << endl;
}

/**
 * ��ѯ������Ϣ
*/
void Artifact::searchArtifact(vector<Artifact>& artifacts) {
	int id;
	cout << "������Ҫ��ѯ��������Ϣ���:";
	cin >> id;
	for (auto it = artifacts.begin(); it != artifacts.end(); ++it) {
		if (it->id == id) {
			cout << "���:" << it->id << ",��������:" << it->name << ",�������:" << it->year << ",չ��״̬:" << it->status <<
				",չ������:" << it->exhibitionCount << ",չ��ʱ��:" << it->exhibitionDuration / 86400 << "��" << 
				endl;
			return;
		}
	}

}

// ��������ķ�������
static int partition(vector<Artifact>& artifacts, int low, int high) {
	Artifact pivot = artifacts[high]; // ѡ�����һ��Ԫ����Ϊ��׼ֵ
	int i = (low - 1); // С�ڻ�׼ֵ��Ԫ�ص�����

	for (int j = low; j <= high - 1; j++) {
		// �����ǰԪ�ش��ڻ���ڻ�׼ֵ��������
		if (artifacts[j].getExhibitionCount() >= pivot.getExhibitionCount()) {
			i++; // ��������i
			std::swap(artifacts[i], artifacts[j]);
		}
	}
	std::swap(artifacts[i + 1], artifacts[high]); // ����׼ֵ�ŵ���ȷ��λ��
	return (i + 1);
}

// ��������ĵݹ麯��
static void quickSort(vector<Artifact>& artifacts, int low, int high) {
	if (low < high) {
		int pi = partition(artifacts, low, high);

		// �ݹ�ضԻ�׼ֵ���ߵ��������������
		quickSort(artifacts, low, pi - 1);
		quickSort(artifacts, pi + 1, high);
	}
}

/**
 * ����չ�������������������
*/
void Artifact::sortArtifact(vector<Artifact>& artifacts) {
	int n = artifacts.size();//��ȡ artifacts������Ԫ�ص�����
	quickSort(artifacts, 0, n - 1); // �ӵ�һ��Ԫ�ص����һ��Ԫ�ؽ�������
	Artifact::printArtifact(artifacts);// ��ӡ������������Ϣ
}


/**
 * �鿴ȫ��������Ϣ
*/
void Artifact::printArtifact(const vector<Artifact>& artifacts) {
	if (artifacts.empty()) {
		cout << "��¼Ϊ�գ�" << endl;
		return;
	}
	for (const auto& artifact : artifacts) {
		cout << "���:" << artifact.id << ",��������:" << artifact.name << ",�������:" << artifact.year <<
			",չ��״̬:" << artifact.status << ",չ������:" << artifact.exhibitionCount <<
			",չ��ʱ��:" << artifact.exhibitionDuration / 86400 << "��"
			<< endl;
	}

}

// ���㻤��ʱ��
time_t Artifact::CalculateCareDuration(time_t exhibitionDuration) {
	// �軤��ʱ����չ��ʱ����10%
	return exhibitionDuration / 10;
}

/**
 * չʾ7����չ��������
*/
void Artifact::caclArtifact(vector<Artifact>& artifacts) {
	time_t currentTime = time(nullptr);// currentTime������ȡ��ǰ��ʱ��
	cout << "7����չ����������ϢΪ:" << endl;
	for (const auto& artifact : artifacts) {
		time_t careDuration = Artifact::CalculateCareDuration(artifact.exhibitionDuration);//ͨ������CalculateCareDuration����õ�����ʱ����
		time_t nextAvailableTime = artifact.exhibitionDuration + careDuration;//�����´ο���չ����ʱ�䣺���ﵱǰչ��ʱ��+����ʱ��
		if (nextAvailableTime <= currentTime + 7 * 24 * 60 * 60) {
			cout << "���:" << artifact.id << ",��������:" << artifact.name << ",�������:" << artifact.year <<
				",չ��״̬:" << artifact.status << ",չ������:" << artifact.exhibitionCount <<
				",չ��ʱ��:" << artifact.exhibitionDuration / 86400<< "��" <<
				 endl;
		}
	}
}


/**
 * ������
*/
int main() {
	vector<Artifact> artifacts;//��������Ϊ artifacts �����������ڴ洢 Artifact ���͵Ķ���
	int choice;//�����û������ѡ��
	while (true) {
		cout << "===============������Ϣ����ϵͳ==================" << endl;
		cout << "*********1.�鿴ȫ��������Ϣ**********" << endl;
		cout << "*********2.�޸�������Ϣ**************" << endl;
		cout << "*********3.�޸�����չ��״̬**********" << endl;
		cout << "*********4.����չ����������������Ϣ**" << endl;
		cout << "*********5.��ѯ������Ϣ**************" << endl;
		cout << "*********6.���������Ϣ**************" << endl;
		cout << "*********7.չʾ7����չ��������Ϣ***" << endl;
		cout << "*********0.�˳�����******************" << endl;
		cout << "��ѡ��:";
		cin >> choice;
		switch (choice) {
		case 0:
			cout << "ϵͳ���˳�,��ӭ�´�ʹ��!" << endl;
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
			cout << "��Ч���룡" << endl;
			break;
		}
	}
	return 0;
}