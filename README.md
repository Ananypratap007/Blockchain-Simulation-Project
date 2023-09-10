# Blockchain Simulation Project

## Overview
Welcome to the Blockchain Simulation Project, a sophisticated and intricate system designed to emulate the core principles of blockchain technology. This project, developed as part of the CS 2413 Data Structures course in Spring 2023, showcases an in-depth understanding of data structures and their practical applications.

## Project Structure
The project is organized into multiple C++ classes, each serving a specific role within the blockchain simulation:

1. Transaction Class: At the heart of the blockchain lies the transaction class. Transactions are the building blocks of any blockchain system. The class meticulously structures each transaction, encapsulating essential details such as transaction ID, source and destination IDs, transaction amount, and a timestamp.

2. Block Class: The block class represents a block within the blockchain. It can accommodate multiple transactions and contains crucial attributes, including the block number, the current number of transactions, and the maximum number of transactions it can hold. This class also includes a vector to store transactions.

3. Blockchain Class: The blockChain class is responsible for maintaining the entire blockchain structure as a linked list of blocks. It can insert transactions into blocks, manage the chain of blocks, and perform critical blockchain operations.

4. Blockchain Network Class: The blockNetwork class orchestrates a network of nodes, with each node housing its blockchain. This class enables the insertion of transactions into the blockchain of the appropriate node based on transaction details.

5. Main Function: The main function serves as the entry point for the simulation. It takes user inputs, including the number of nodes in the network, the maximum transactions per block, the total number of transactions, and the connections between nodes. It processes transactions, creates blocks, and displays the state of the entire blockchain network.


## Complexity and Features
This project exhibits complexity and sophistication in several aspects:

1. Multiple Classes
The project utilizes object-oriented programming principles by employing various classes to represent transactions, blocks, blockchains, and the network. This modular approach enhances code organization, maintainability, and readability.

2. Linked List Structure
The blockchain itself is implemented as a linked list of blocks. This design choice mirrors the real-world structure of blockchain networks, where each block references the previous one.

3. Transaction Handling
The project meticulously manages transactions, ensuring that they are correctly processed, validated, and inserted into the blockchain. It handles scenarios where users may have insufficient funds or where transactions exceed block capacity.

4. Error Handling
Though not explicitly mentioned in the code, error handling would be a crucial aspect to consider in a production-ready blockchain. Error scenarios, such as double spending or invalid transactions, would need to be addressed.

5. Network Simulation
The blockNetwork class simulates a network of nodes, each running its blockchain. This emulates the decentralized nature of real-world blockchain networks like Bitcoin and Ethereum.

## Usage
To run the blockchain simulation, follow these steps:

- Compile the code using a C++ compiler.

- Execute the compiled binary.

- Provide inputs as requested, including the number of nodes, maximum transactions per block, total number of transactions, and node connections.

- Observe the simulation as it processes transactions, creates blocks, and displays the blockchain network's state.

## Use Case

### 1. Inserting Transactions into a Block
In the block class, the insertTransaction method is responsible for inserting a new transaction into a block. Below is a code snippet for this important functionality:

```cpp
// block class
class block {
    // ...
public:
    // ...
    
    // Insert method to insert a new transaction into the block
    void insertTransaction(int numNode, transaction t) {
        cout << "Inserting transaction to block #" << blockNumber << " in node " << numNode << endl;
        bTransactions[currentNumTransactions] = t;
        currentNumTransactions++;
        return;
    }
    
    // ...
};
```
#### Use Case:
In the blockchain simulation, whenever a new transaction is created and needs to be added to a block, the insertTransaction method is called. For example:
```cpp
transaction t(/* transaction details */);
block newBlock(/* block details */);
newBlock.insertTransaction(nodeNumber, t);
```

### 2. Searching for an ID's Current Value in the Blockchain
In the block class, there's a searchIDGetValue method that searches for a specific ID's current value by iterating through the blockchain's transactions. Below is a code snippet for this functionality:

```cpp
// block class
class block {
    // ...
public:
    // ...
    
    // Search for an ID and get its current value
    int searchIDGetValue(int ID) {
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
                } else if (tempToId == ID) {
                    calculatedFromValue = bTransactions[i].getToValue() + bTransactions[i].getTAmount();
                    return calculatedFromValue;
                }
            }
        }
        return calculatedFromValue;
    }
    
    // ...
};
```
#### Use Case:
To retrieve the current value of an ID in the blockchain, you can call the searchIDGetValue method. For example:
```cpp
block someBlock(/* block details */);
int IDToSearch = 123; // Replace with the actual ID you want to search for
int currentValue = someBlock.searchIDGetValue(IDToSearch);
if (currentValue != -1) {
    cout << "Current value of ID " << IDToSearch << ": " << currentValue << endl;
} else {
    cout << "ID " << IDToSearch << " not found in the blockchain." << endl;
}
```

These use cases demonstrate just a few of many features of the project.


## Conclusion
The Blockchain Simulation Project demonstrates a profound understanding of data structures and their application in creating a simplified yet impressive blockchain network. It serves as a foundation for understanding the inner workings of real-world blockchain systems and paves the way for further exploration of blockchain technology.

This project showcases the complexity and intricacies involved in building and simulating a blockchain network, highlighting the developer's expertise in data structures and software design.
