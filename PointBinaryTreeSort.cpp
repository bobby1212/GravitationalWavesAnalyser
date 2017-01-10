#include "PointBinaryTreeSort.h"



PointBinaryTreeSort::PointBinaryTreeSort()
{
}


PointBinaryTreeSort::~PointBinaryTreeSort()
{
}

std::list<Point*> PointBinaryTreeSort::SortPointsXAxis(std::vector<Point>* points)
{
    Tree* root;
    root = nullptr;

    for (int i = 0; i < points->size(); i++)
    {
        insert(&root, points->begin()+i);
    }

    addToList(root);

    return sortedPoints;
}

void PointBinaryTreeSort::insert(Tree** root, std::vector<Point>::iterator newValue)
{
    Tree* temp;
    Tree* parent;

    if ((*root) == nullptr)
    {
        (*root) = new Tree();
        (*root)->point = &*newValue;
        (*root)->left = nullptr;
        (*root)->right = nullptr;
    }
    else
    {
        temp = (*root);

        while (temp != nullptr)
        {
			if ((&*newValue)->x == temp->point->x)
			{
				if ((&*newValue)->y < temp->point->y)
				{
					parent = temp;
					temp = temp->left;
				}
				else
				{
					parent = temp;
					temp = temp->right;
				}
			}
            else if ((&*newValue)->x < temp->point->x)
            {
                parent = temp;
                temp = temp->left;
            }
            else
            {
                parent = temp;
                temp = temp->right;
            }
        }

        Tree* newNode = new Tree();
        newNode->point = &*newValue;
        newNode->left = nullptr;
        newNode->right = nullptr;

		if ((&*newValue)->x == parent->point->x)
		{
			if ((&*newValue)->y < parent->point->y)
			{
				parent->left = newNode;
			}
			else
			{
				parent->right = newNode;
			}
		}
		else if ((&*newValue)->x <= parent->point->x)
            parent->left = newNode;
        else
            parent->right = newNode;
    }
}

void PointBinaryTreeSort::addToList(Tree* node)
{

    if (node == nullptr)
        return;
    else
    {
        addToList(node->left);
        sortedPoints.push_back(node->point);
        addToList(node->right);
    }

}
