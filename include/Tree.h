#include <Shader.h>
#include <Model.h>
#include <CollidableBody.h>

#include <functional>

class Tree {

public:
	std::vector<CollidableBody> treeBody;
	Tree();
	void drawTrees(Shader& shader);
	vector<glm::vec3> getTreePositions();

	//void collectPosition(glm::vec3 treePos);

	glm::vec3 feedbackPaperPosition();

	void forEachTree(const std::function<void(CollidableBody&)>& action);

private:

	int forestSize = 20;
	int treeSpacing = 10;
	std::unique_ptr<class Model> treeModel;
	std::vector<glm::mat4> treeTransform;
	void generateTreesTransforms();
};


