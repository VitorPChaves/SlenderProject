#include <Shader.h>
#include <Model.h>
#include <CollidableBody.h>

class Tree {

public:
	
	Tree();
	void drawTrees(Shader& shader);

private:

	int forestSize = 50;
	int treeSpacing = 10;
	std::unique_ptr<class Model> treeModel;
	CollidableBody treeBody;
	std::vector<glm::mat4> treeTransform;

	void generateTreesTransforms();
		
};


