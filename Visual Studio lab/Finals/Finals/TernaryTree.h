

// COS30008, Final Exam, 2023

#pragma once
#include <stdexcept>
#include <algorithm>

template<typename T>
class TernaryTreePrefixIterator;

template<typename T> class
TernaryTree
{
public:
	using TTree = TernaryTree<T>;
	using TSubTree = TTree*;
private:
	T fKey;
	TSubTree fSubTrees[3];
	// private default constructor used for declaration of NIL
	TernaryTree() :
		fKey(T()) {
		for (size_t i = 0; i < 3; i++)
		{
			fSubTrees[i] = &NIL;
		}
	}
public:
	using Iterator = TernaryTreePrefixIterator<T>;
	static TTree NIL; // sentinel
	// getters for subtrees
	const TTree& getLeft() const { return *fSubTrees[0]; }
	const TTree& getMiddle() const { return *fSubTrees[1]; }
	const TTree& getRight() const { return *fSubTrees[2]; }
	// add a subtree
	void addLeft(const TTree& aTTree) { addSubTree(0, aTTree); }
	void addMiddle(const TTree& aTTree) { addSubTree(1, aTTree); }
	void addRight(const TTree& aTTree) { addSubTree(2, aTTree); }
	// remove a subtree, may through a domain error const
	const TTree& removeLeft() { return removeSubTree(0); }
	const TTree& removeMiddle() { return removeSubTree(1); }
	const TTree& removeRight() { return removeSubTree(2); }
	////////////////////////////////////////////////////////////
/////////////
	// Problem 1: TernaryTree Basic Infrastructure

private:
	// remove a subtree, may throw a domain error [22]
	const TTree& removeSubTree(size_t aSubtreeIndex)
	{
		if ((aSubtreeIndex < 0) || (aSubtreeIndex > 2))
			throw std::out_of_range("Illegal subtree index");

		if (fSubTrees[aSubtreeIndex]->empty())
			throw std::domain_error("Subtree is NIL");

		TTree& result = *fSubTrees[aSubtreeIndex];
		fSubTrees[aSubtreeIndex] = &NIL;

		return result;
	}

	// add a subtree; must avoid memory leaks; may throw domain error [18]
	void addSubTree(size_t aSubtreeIndex, const TTree& aTTree)
	{
		if ((aSubtreeIndex < 0) || (aSubtreeIndex > 2))
			throw std::out_of_range("Illegal subtree index");

		if (!fSubTrees[aSubtreeIndex]->empty())
			throw std::domain_error("Subtree is not NIL");

		fSubTrees[aSubtreeIndex] = const_cast<TTree*>(&aTTree);
	}

public:
	// TernaryTree l-value constructor 
	TernaryTree(const T& aKey) : fKey(aKey), fSubTrees{}
	{
		for (size_t i = 0; i < 3; i++)
		{
			fSubTrees[i] = &NIL;
		}
	}

	// destructor (free sub-trees, must not free empty trees)
	~TernaryTree()
	{
		for (size_t i = 0; i < 3; i++)
		{
			if (!fSubTrees[i]->empty())
				delete fSubTrees[i];
		}
	}

	// return key value, may throw domain_error if empty
	const T& operator*() const
	{
		if (empty())
		{
			throw std::domain_error("Subtree is NIL");
		}

		return fKey;
	}

	// returns true if this ternary tree is empty
	bool empty() const
	{
		return this == &NIL;
	}

	// returns true if this ternary tree is a leaf
	bool leaf() const
	{
		return fSubTrees[0]->empty() && fSubTrees[1]->empty() && fSubTrees[2]->empty();
	}

	size_t height() const
	{
		if (empty())
		{
			throw std::domain_error("Operation not supported");
		}
		else if (leaf())
		{
			return 0;
		}
		else
		{
			size_t subtreeHeight = 0;
			for (size_t i = 0; i < 3; i++)
			{
				if (!fSubTrees[i]->empty())
				{
					size_t currentHeight = fSubTrees[i]->height();
					if (currentHeight > subtreeHeight)
					{
						subtreeHeight = currentHeight;
					}
				}
			}
			return subtreeHeight + 1;
		}
	}
	/////////////////////////////////////////////////////////////////////////
	// Problem 2: TernaryTree Copy Semantics
	// Copy constructor
	TernaryTree(const TTree& aOtherTTree) : fKey(T()), fSubTrees{}
	{
		if (aOtherTTree.empty())
			throw std::domain_error("Unable to copy NIL");

		for (size_t i = 0; i < 3; i++)
		{
			if (aOtherTTree.fSubTrees[i] != &NIL)
				fSubTrees[i] = new TTree(*aOtherTTree.fSubTrees[i]);
			else
				fSubTrees[i] = &NIL;
		}
	}

	// Copy assignment operator
	TTree& operator=(const TTree& aOtherTTree)
	{
		if (aOtherTTree.empty())
			throw std::domain_error("NIL as source not permitted.");

		fKey = aOtherTTree.fKey;

		for (size_t i = 0; i < 3; i++)
		{
			if (!aOtherTTree.fSubTrees[i]->empty())
			{
				fSubTrees[i] = aOtherTTree.fSubTrees[i]->clone();
			}
			else
			{
				fSubTrees[i] = &NIL;
			}
		}
	}
	

	// Clone method
	TSubTree clone() const
	{
		if (empty())
			throw std::domain_error("Unable to clone NIL");

		return new TTree(*this);
	}
	/////////////////////////////////////////////////////////////////////////
	// Problem 3: TernaryTree Move Semantics
	// TTree r-value constructor [12]
	TernaryTree(T&& aKey): fKey(T()), fSubTrees{}
	{
		fKey = std::move(aKey);
		for (size_t i = 0; i < 3; i++) {
			fSubTrees[i] = &NIL;
		}
	}
	// move constructor, must not copy empty ternary tree [12]
	TernaryTree(TTree&& aOtherTTree)
	{
		if (aOtherTTree.empty())
			throw std::domain_error("Cannot copy empty ternary tree");

		for (size_t i = 0; i < 3; i++)
		{
			fSubTrees[i] = &NIL;
		}

		*this = std::move(aOtherTTree);
	}

	// move assignment operator, must not copy empty ternary tree
	TTree& operator=(TTree&& aOtherTTree)
	{
		if (this != &aOtherTTree)
		{
			if (aOtherTTree.empty())
			{
				throw std::domain_error("NIL as source not permitted.");
			}

			fKey = std::move(aOtherTTree.fKey);

			for (size_t i = 0; i < 3; i++)
			{
				if (aOtherTTree.fSubTrees[i]->empty())
				{
					fSubTrees[i] = &NIL;
				}
				else
				{
					fSubTrees[i] = aOtherTTree.fSubTrees[i];
					aOtherTTree.fSubTrees[i] = &NIL;
				}
			}
		}

		return *this;
	}
	/////////////////////////////////////////////////////////////////////////
	// Problem 4: TernaryTree Prefix Iterator
	// return ternary tree prefix iterator positioned at start [4]
	Iterator begin() const;
	// return ternary prefix iterator positioned at end [6]
	Iterator end() const;
};
template<typename T>
TernaryTree<T> TernaryTree<T>::NIL;
