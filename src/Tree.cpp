#include <Tree.h>

Tree::Tree() : treeBody(BoundingBox(glm::vec3(0), glm::vec3(0)), false)
{
	treeModel = std::make_unique<Model>("../images/Tree2/Tree.obj");
	treeP = glm::vec3(0);
	treeBody.setPosition(treeP);
}

glm::vec3 Tree::getTreePos() {
	return treeP;
}

void Tree::setTreePos(glm::vec3 newPosition) {
	treeP = newPosition;
}

void Tree::drawTrees(Shader& shader) {

}

// Gerar uma posição randomica
// Armazenar essa posição
// Passar as posições
// Desenhar