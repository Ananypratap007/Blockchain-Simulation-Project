// Project 4
// CS 2413 Data Structures
// Spring 2023

#include <iostream>
#include <vector> // for array of transactions and array of blockChains
#include <list>   // for array of blocks

using namespace std;


// this class is simple data type of class
//just complete the structure of a transaction object
class transaction
{
	int tID;          // transaction id----------------------------------> given input
	int fromID;       // source ID --------------------------------------> given input
	int fromValue;    // P4: how much funds does the source ID person have? If first time, then initialize with 100 coins
	int toID;         // target ID ---------------------------------------> given input
	int toValue;      // P4: how much funds does the source ID person have? If first time, then initialize with 100 coins
	int tAmount;      // how much is being transfered
	string timeStamp; // time of the transaction read from the input file

public:
	transaction() : tID(0), fromID(0), toID(0), tAmount(0), timeStamp("") {} // default constructor

	transaction(int temptID, int tempfromID, int temptoID, int temptAmount, string temptimeStamp) {
		tID = temptID;
		fromID = tempfromID;
		fromValue = 100;
		toID = temptoID;
		toValue = 100;
		tAmount = temptAmount;
		timeStamp = temptimeStamp;
	}

	transaction(int temptID, int tempfromID, int tempfromValue, int temptoID, int tempToValue, int temptAmount, string temptimeStamp) {
		tID = temptID;
		fromID = tempfromID;
		fromValue = tempfromValue;
		toID = temptoID;
		toValue = tempToValue;
		tAmount = temptAmount;
		timeStamp = temptimeStamp;
	}

	// all setters and getters
	int getTID() const { return tID; }
	void setTID(int id) { tID = id; }

	int getFromID() const { return fromID; }
	void setFromID(int id) { fromID = id; }

	int getFromValue() const { return fromValue; }
	void setFromValue(int value) { fromValue = value; }

	int getToID() const { return toID; }
	void setToID(int id) { toID = id; }

	int getToValue() const { return toValue; }
	void setToValue(int value) { toValue = value; }

	int getTAmount() const { return tAmount; }
	void setTAmount(int amount) { tAmount = amount; }

	string getTimeStamp() const { return timeStamp; }
	void setTimeStamp(string time) { timeStamp = time; }

	// this diplay method will be called in block class's display method
	//while iterating though the loop
	void displayTransaction() {
		cout << tID << " " << fromID << " " << fromValue << " " << toID << " " << toValue << " " <<
			tAmount << " " << timeStamp << endl;
	}
};
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Some comments for output
//Each time a transaction is add to a new block this line should be printed->
// "Adding block #1"
// After this as each transaction is added to block 1 -> "Inserting Transaction to block #1"

// this class will have vector of transactions
class block
{
	int blockNumber; // block number of the current block
	int currentNumTransactions; // how many transactions are currently in the block
	int maxNumTransactions; // how many maximum transactions can be in the block
	vector<transaction> bTransactions; // vector of transaction objects

public:
	block() {} // default constructor

	// non default constructor
	block(int bNumber, int maxTransactions) {
		this->blockNumber = bNumber;
		this->currentNumTransactions = 0;
		this->maxNumTransactions = maxTransactions;
		this->bTransactions.resize(maxTransactions);
	}

	int searchIDGetValue(int ID) { // this will return the from value
		int tempFromId;
		int tempToId;
		int calculatedFromValue = -1;
		for (int i = currentNumTransactions - 1; i >= 0; i--) {

			tempFromId = bTransactions[i].getFromID();
			tempToId = bTransactions[i].getToID();

			if (tempFromId == ID || tempToId == ID) {
			
				if (tempFromId == ID) {
					calculatedFromValue = bTransactions[i].getFromValue() - bTransactions[i].getTAmount();
					return calculatedFromValue;
				}
				else if (tempToId == ID) {
					calculatedFromValue = bTransactions[i].getToValue() + bTransactions[i].getTAmount();
					return calculatedFromValue;
				}
			}
		}
		return calculatedFromValue;
	}



	// insert method to insert a new transaction
	void insertTransaction(int numNode, transaction t)
	{    
		cout << "Inserting transaction to block #" << blockNumber << " in node " << numNode << endl;
		bTransactions[currentNumTransactions] = t;
		currentNumTransactions++;
		return;
	}

	// setters and getters as needed
	int getBlockNumber() { return blockNumber; }
	void setBlockNumber(int num) { blockNumber = num; }

	int getCurrentNumTransactions() { return currentNumTransactions; }
	void setCurrentNumTransactions(int num) { currentNumTransactions = num; }

	int getMaxNumTransactions() { return maxNumTransactions; }
	void setMaxNumTransactions(int num) { maxNumTransactions = num; }

	vector<transaction> getBTransactions() { return bTransactions; }
	void setBTransactions(vector<transaction> transactions) { bTransactions = transactions; }


	//display method which will be called from the blockchain class 
	void displayBlock() {
		cout << "Block Number: " << blockNumber << " -- Number of Transaction: " << currentNumTransactions << endl;

		for (int i = 0; i < currentNumTransactions; i++) {
			// calling display method of transaction class
			bTransactions[i].displayTransaction(); // display method will be called for each transaction object stored int the vector
		}
	}
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// this class will have linked list of blocks
class blockChain
{
	int currentNumBlocks; // maintain the size of the list/block chain list
	list<block> bChain; // blockchain as a linked list
	int numTransactionsPerBlock; // max transactions per block

public:
	//default
	blockChain() {
		this->currentNumBlocks = 0;
		this->numTransactionsPerBlock = 0;
	}
	// non default
	blockChain(int transPerBlock) {
		this->currentNumBlocks = 0;
		this->numTransactionsPerBlock = transPerBlock;
	}

	// insert method to insert new transaction into the block chain - add new block if existing block is full
	void insertTransaction(int numNode, transaction t)
	{

		if (bChain.empty() || bChain.back().getCurrentNumTransactions() == numTransactionsPerBlock)
		{
			block newBlock(currentNumBlocks + 1, numTransactionsPerBlock);
			newBlock.insertTransaction(numNode, t);
			bChain.push_back(newBlock);
			currentNumBlocks++;
		}
		else
		{
			bChain.back().insertTransaction(numNode, t);
		}
	}

	// P4: search for an ID across all blocks in bChain

	int searchIDGetValue(int ID) {
	    int tempValue = -1;
		for (std::list<block>::reverse_iterator it = bChain.rbegin(); it != bChain.rend(); ++it) {
			tempValue = it->searchIDGetValue(ID);
			if (tempValue != -1) {
				return tempValue;
			}
		}
		 return tempValue;
	}


	// setters and getters as needed
	int getCurrentNumBlocks() { return currentNumBlocks; }
	void setCurrentNumBlocks(int num) { currentNumBlocks = num; }

	list<block> getBChain() { return bChain; }
	void setBChain(list<block> chain) { bChain = chain; }

	int getNumTransactionsPerBlock() { return numTransactionsPerBlock; }
	void setNumTransactionsPerBlock(int num) { numTransactionsPerBlock = num; }

	//display method which will be called in the main method
	void displayData() {
		for (std::list<block>::iterator it = bChain.begin(); it != bChain.end(); ++it) {
			it->displayBlock(); //calling diplay method from the block class
		}

	}
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class blockNetwork
{
	int numNodes;                // maintain the number of nodes in the network
	vector<blockChain> allNodes; // vector of all the blockChains in the network
	vector<int> u;               // edge list u node
	vector<int> v;               // edge list v node
	int tPerBlock;

public:
	blockNetwork() {
		this->numNodes = 0;                 // default constructor
	}

	blockNetwork(int numberOfNodes, int numEdges, int transPerBlock) { // non default constructor
		this->numNodes = numberOfNodes;
		this->allNodes.resize(numberOfNodes);
		for (int i = 0; i < numberOfNodes; i++) {
			allNodes[i].setNumTransactionsPerBlock(transPerBlock);
		}
		this->u.resize(numEdges);
		this->v.resize(numEdges);
		this->tPerBlock = transPerBlock;
	}


	//insert method to insert new transaction into the block chain in a specific node - there will be a block chain existent in each node (allNodes vector)
	void insertTransaction(int nodeNum, transaction t)
	{   
		int tempFromValue;
		tempFromValue = allNodes[nodeNum].searchIDGetValue(t.getFromID());

		int tempToValue;
		tempToValue = allNodes[nodeNum].searchIDGetValue(t.getToID());
        
		if (tempFromValue != -1 && tempToValue != -1) {
			transaction tempTransaction(t.getTID(), t.getFromID(),tempFromValue, t.getToID(), tempToValue, t.getTAmount(), t.getTimeStamp());
			allNodes[nodeNum].insertTransaction(nodeNum, tempTransaction);
		}
		else if (tempFromValue != -1 && tempToValue == -1) {
			transaction tempTransaction(t.getTID(), t.getFromID(), tempFromValue, t.getToID(), 100, t.getTAmount(), t.getTimeStamp());
			allNodes[nodeNum].insertTransaction(nodeNum, tempTransaction);
		}
		else if (tempFromValue == -1 && tempToValue != -1) {
			transaction tempTransaction(t.getTID(), t.getFromID(), 100, t.getToID(), tempToValue, t.getTAmount(), t.getTimeStamp());
			allNodes[nodeNum].insertTransaction(nodeNum, tempTransaction);
		}
		else if (tempFromValue == -1 && tempToValue == -1) {
			transaction tempTransaction(t.getTID(), t.getFromID(), 100, t.getToID(), 100, t.getTAmount(), t.getTimeStamp());
			allNodes[nodeNum].insertTransaction(nodeNum, tempTransaction);
		}
		else {
			transaction tempTransaction(t.getTID(), t.getFromID(), 100, t.getToID(), 100, t.getTAmount(), t.getTimeStamp());
			allNodes[nodeNum].insertTransaction(nodeNum, tempTransaction);
		}
	}



	// setters and getters as needed
	vector<int> getU() { return u; }
	void setU(vector<int> tempU) { u = tempU; }

	vector<int> getV() { return v; }
	void setV(vector<int> tempV) { u = tempV; }


	// other methods as needed
	//TODO: Display method
	void displayBlockNetwork() {


		for (int i = 0; i < numNodes; i++) {
			cout << "~~~ Node " << i << ": " << endl;
			cout << "Current number of blocks: " << allNodes[i].getCurrentNumBlocks() << endl;
			allNodes[i].displayData();
		}
	}
};
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int main() {

	int numNodesInNetwork; // number of nodes in the network

	cin >> numNodesInNetwork;//--------------------------------------------------------------------------->   4
	cout << "Number of nodes: " << numNodesInNetwork << endl;

	int numTransactionsPerBlock; // max transactions per block

	cin >> numTransactionsPerBlock; //--------------------------------------------------------------------->  10
	cout << "Number of transactions per block: " << numTransactionsPerBlock << endl;

	int totalNumTransactions; // total transactions to be read from the input file
	cin >> totalNumTransactions;    //--------------------------------------------------------------------->  27
	cout << "Total number of transactions: " << totalNumTransactions << endl;

	int numEdges;
	cin >> numEdges;

	// object of block network
	blockNetwork* n1 = new blockNetwork(numNodesInNetwork, numEdges, numTransactionsPerBlock);

	//set U and V
	vector<int> tempU = n1->getU();
	vector<int> tempV = n1->getV();
	for (int i = 0; i < numEdges; i++) {
		cin >> tempU[i] >> tempV[i];
	}
	n1->setU(tempU);
	n1->setV(tempV);


	for (int i = 0; i < totalNumTransactions; i++) {
		int numNode, tID, fromID, toID, tAmount;
		string timeStamp;
		cin >> numNode >> tID >> fromID >> toID >> tAmount >> timeStamp;

		transaction t(tID, fromID, toID, tAmount, timeStamp);
		n1->insertTransaction(numNode, t);
	}

	//TODO: Display the information
	n1->displayBlockNetwork();


	delete n1;
	return 0;
}

//Problems- 1) With the insertion method adding blockchains
// problem- 2) with the pointers and null pointers in the search method