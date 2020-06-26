#include <Shader.h>
#include <Model.h>
#include <CollidableBody.h>
//#include <vector>

class Tree {

public:
	
	Tree();
	
	//glm::vec3 getTreePos();

	//void setTreePos(glm::vec3& newPosition);

	//void transformTree(Shader* shader, int x, int z);

	//void positionate(Shader& shader);

	//void storeTrees(Shader& shader);

	void drawTrees(Shader& shader);

private:
	void generateTreesTransforms();

private:
	bool draw = false;
	int x, z;
	int cont = 1;
	int forestSize = 50;
	int treeSpacing = 10;
	std::unique_ptr<class Model> treeModel;
	CollidableBody treeBody;
	//std::vector<glm::vec3> treeP;

	std::vector<glm::mat4> treeTransform;
		
};


