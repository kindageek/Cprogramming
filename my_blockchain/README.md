# My_blockchain in C programming language

This is a simple and custom blockchain implementation in C programming language.

Blockchain is a command that allows for the creation and management of a blockchain. When the program starts (it loads a backup if there is one) then a prompt appears. This prompt allows to execute commands. When the commands are not successful they display "**nok: *info***" or *info* is an error message - see below:

- **add node *nid*** add a *nid* identifier to the blockchain node.
- **rm node *nid...*** remove nodes from the blockchain with a *nid* identifier. If **nid** is '*', then all nodes are impacted.
- **add block *bid* *nid...*** add a *bid* identifier block to nodes identified by *nid*. If **nid** is '*', then all nodes are impacted.
- **rm block *bid...*** remove the *bid* identified blocks from all nodes where these blocks are present.
- **ls** list all nodes by their identifiers. The option **-l** attaches the blocks bid's associated with each node.
- **sync** synchronize all of the nodes with each other. Upon issuing this command, all of the nodes are composed of the same blocks.
- **quit** save and leave the blockchain.

The blockchain prompt displays:

- a **[** character
- a first letter that indicates the state of synchronization of the chain:
    - "**s**" if the blockchain is synchronized
    - "**-**" if the blockchain is not synchronized.
- **n** number of nodes in the chain.
- the "**]>** " string (with a space)

## Error messages

- nok: no more resources available on the computer
- nok: this node already exists
- nok: this block already exists
- nok: node doesn't exist
- nok: block doesn't exist
- nok: command not found
- nok: incorrect number arguments
- nok: no nodes in the blockchain

## Technical information

```cpp
$>my_blockhain
[s0]> add node 12
[s1]> add block 21 *
[s1]> add node 13
[-2]> sync
[s2]> ls -l
12: 21
13: 21
[s2]> quit
```

- The design of the blockchain was implemented using custom two-sided linked list, where the blockchain starts with a head node, having pointer to its blocks and the next node. All nodes have pointers to their own linked list of blocks.

```cpp
typedef struct blockchain_block
{
    char* bid;
    int nid;
    struct blockchain_block* next;
}block;

typedef struct blockchain_node
{
    int nid;
    struct blockchain_block* block;
    struct blockchain_node* next;
}node;
```

- When the program is run, it loads the backup blockchain data from *backup.txt* file, and saves the data to that file on `quit` command. The data is stored with a specific format, writing node id and it's blocks' ids in one line separated by a space:

```
nid1 bid1 bid2 bid3 ...
nid2 bid1 bid2 ...
nid3 bid1 ...
...
```

- The program has no memory leaks and can be run with flags `-g3 fsanitize=leak` and `-Wall -Wextra -Werror` .

## How to use it?

- Download or clone the repository
- Open the terminal and go to the project folder
- Type `make` and compile the files
- Type `./my_blockchain` and run the program
- Use the commands listed above

## Conclusion

As a result of this project, I learned a lot about blockchain and how to implement it, which I have never tried before. This project taught me how to design a relatively large project, dividing it into partitions and connect them with each other, and also how to create custom complex data structures and manipulate them. Moreover, the program has no memory leaks and I spent quite a lot of time learning how to ensure that.
