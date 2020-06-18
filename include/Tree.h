#include <Shader.h>
#include <Model.h>
#include <CollidableBody.h>

class Tree {

public:
	
	Tree();
	
	glm::vec3 getTreePos();

	void setTreePos(glm::vec3 newPosition);

	void drawTrees(Shader& shader);

private:
	std::unique_ptr<class Model> treeModel;
	CollidableBody treeBody;
	glm::vec3 treeP;

};