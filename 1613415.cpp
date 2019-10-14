#include<iostream>
#include<vector>
#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;

int MaxProfit_1(const vector<int> prices) {
	if (prices.size() <= 1)
		return 0;
	int min_price = prices[0];
	int max_profit = 0;
	for (int i = 0; i < prices.size(); i++)
	{
		min_price = min(min_price, prices[i]);
		max_profit = max(max_profit, prices[i] - min_price);
	}
	return max_profit;
}
int MaxProfit_2(const vector<int> prices) {
	int max_profit = 0;
	for (int i = 1; i < prices.size(); i++) {
		if (prices[i] > prices[i - 1])
			max_profit += prices[i] - prices[i - 1];
	}
	return max_profit;
}
int MaxProfit_3(const vector<int> prices, int fee) {
	if (prices.size() < 2)
		return 0;
	int max_profit = 0;
	int mini = prices[0];
	for (int i = 0; i < prices.size(); i++)
	{
		if (prices[i] < mini) //��ǰ�ĸ�С
			mini = prices[i];
		else if (prices[i] > mini + fee) //��ǰ�ϴ���������
		{
			max_profit += prices[i] - fee - mini;
			mini = prices[i] - fee;
		}
	}
	return max_profit;
}
int MaxProfit_4(const vector<int> prices) 
{
	if (prices.size() < 2)
		return 0;
	vector<int> sell(prices.size());
	vector<int> cold(prices.size());
	vector<int> buy(prices.size());

	buy[0] = -prices[0];
	for (int i = 1; i < prices.size(); i++)
	{
		sell[i] = max(buy[i - 1] + prices[i], sell[i - 1]);
		buy[i]  = max(cold[i - 1] - prices[i], buy[i - 1]);
		cold[i] = max(max(sell[i - 1], buy[i - 1]), cold[i - 1]);
	}
	return sell[prices.size() - 1];
}
int MaxProfit_5(const vector<int> prices) 
{
	int FirstBuy  = -prices[0], FirstSell = 0;
	int SecondBuy = -prices[0], SecondSell = 0;
	for(int i=0;i<prices.size();i++)
	{
		FirstBuy   = max(FirstBuy, -prices[i]);
		FirstSell  = max(FirstSell, FirstBuy + prices[i]);
		SecondBuy  = max(SecondBuy, FirstSell - prices[i]);
		SecondSell = max(SecondSell, SecondBuy + prices[i]);
	}
	int max_profit = SecondSell;
	return max_profit;
}
int MaxProfit_6(const vector<int> prices, int k)
{
	if (prices.size() <= 1 || k == 0)
		return 0;
	if (k >= prices.size() / 2) // k���ڵ������鳤��һ��ʱ,����ת��Ϊ̰������
								// ��ʱֱ�Ӳ�������2��̰�ķ���������Դ������ʱ������
		return MaxProfit_2(prices);
	vector<vector<int>> stock(k);
	for (int i = 0; i < k; i++)
	{
		stock[i].push_back(-prices[0]); // ��ĳ���i�������Ʊ�ɻ�õ��������
		stock[i].push_back(0);          // ��ĳ���i��������Ʊ�ɻ�õ��������
	}
	for (int i = 0; i < prices.size(); i++)
	{
		stock[0][0] = max(stock[0][0], -prices[i]);
		stock[0][1] = max(stock[0][1], stock[0][0] + prices[i]);
		for (int j = 1; j < k; j++)
		{
			stock[j][0] = max(stock[j][0], stock[j - 1][1] - prices[i]);
			stock[j][1] = max(stock[j][1], stock[j][0] + prices[i]);
		}
	}
	int max_profit = stock[k - 1][1];
	return max_profit;
}

void stock(const vector<int> prices)
{
	cout << "�ɼ�����Ϊ��";
	for (int i = 0; i < prices.size(); i++)
		cout << prices[i] << ' ';
	cout << endl;
}
int main()
{
	vector<int> prices1 = { 7,1,5,3,6,4 };
	stock(prices1);
	cout << "������1�����µ�������� = " << MaxProfit_1(prices1) << endl << endl;

	vector<int> prices2 = { 1,2,3,4,5 };
	stock(prices2);
	cout << "������2�����µ�������� = " << MaxProfit_2(prices2) << endl << endl;

	vector<int> prices3 = { 1,3,2,8,4,9 };
	stock(prices3);
	cout << "������ = " << 2 << endl;
	cout << "������3�����µ�������� = " << MaxProfit_3(prices3, 2) << endl << endl;

	vector<int> prices4 = { 1,2,3,0,2 };
	stock(prices4);
	cout << "������4�����µ�������� = " << MaxProfit_4(prices4) << endl << endl;

	vector<int> prices5 = { 3,3,5,0,0,3,1,4 };
	stock(prices5);
	cout << "������5�����µ�������� = " << MaxProfit_5(prices5) << endl << endl;

	vector<int> prices6 = { 3,2,6,5,0,3 };
	stock(prices6);
	cout << "�����Բ��� " << 2 << " ��" << endl;
	cout << "������6�����µ�������� = " << MaxProfit_6(prices6, 2) << endl << endl;

	return 0;

}