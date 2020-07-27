#include <Tree.h>
#include <glm/gtx/matrix_decompose.hpp>

Tree::Tree()
{
	treeModel = std::make_unique<Model>("../images/Tree2/Tree.obj");
    generateTreesTransforms();

	treeBody.reserve(treeTransform.size());
	for each (const auto & m in treeTransform) {
		treeBody.push_back(CollidableBody(BoundingBox(glm::vec3(-0.5f), glm::vec3(0.5f)), true));
	}
	vector<glm::vec3> treePositions = getTreePositions();
	for (int i = 0; i < treePositions.size(); i++) {
		treeBody[i].setPosition(treePositions[i]);
	}
}

void Tree::forEachTree(const std::function<void(CollidableBody&)>& action) {
	for (int i = 0; i < treeBody.size(); ++i) {
		action(treeBody[i]);
	}
}

glm::vec3 Tree::feedbackPaperPosition() {

    vector<glm::vec3> const positions = getTreePositions();
    //a funcao getTreePosition pega a posição das arvores toda hora
        //se essa posição é constantemente mutável
        //sendo assim, a posição das pistas muda toda hora também
    //esse vetor tem que conter todas as posições
    glm::vec3 posXisZe;

    bool check = false;
    float xposition = 0;
    float zposition = 0;
    while (check == false) {
        for (int i = 0; i < positions.size(); i++) {
            float seed = glfwGetTime();
            srand(seed);
            xposition = rand() % 30;
            zposition = rand() % 30;

            if (xposition == positions[i].x && zposition == positions[i].z) {
                seed = glfwGetTime();
                srand(seed);
                xposition = rand() % 30;
                zposition = rand() % 30;
            }
        }
        posXisZe = glm::vec3(xposition, 0.3f, zposition);
        break;
    }
    return posXisZe;
}

void Tree::generateTreesTransforms() {
    srand(0);

    for (int x = -50; x < forestSize; x += treeSpacing) {
        for (int z = -50; z < forestSize; z += treeSpacing) {

            glm::mat4 model = glm::mat4(1.0f);

            int xOffset = rand() % 50;
            int zOffset = rand() % 50;
            float treeRotateOffset = rand() % 360;
            float treeScaleOffset = rand() % 3 + 2;

            glm::vec3 treePos = glm::vec3(x + xOffset, 0.0f, z + zOffset);

            model = translate(model, treePos);
            model = scale(model, glm::vec3(treeScaleOffset));
            model = rotate(model, glm::radians(treeScaleOffset), glm::vec3(0.0f, 1.0f, 0.0f));
            treeTransform.push_back(model);            
        }
    }
}

void Tree::drawTrees(Shader& shader) {
    for each (const auto& m in treeTransform) {
        shader.setMat4("model", m);
        treeModel->Draw(shader);
    }
}

vector<glm::vec3> Tree::getTreePositions() {
	vector<glm::vec3> treePositions;
	glm::vec3 treePosition;
	for each (const auto & m in treeTransform) {
		treePosition = m[3];
		treePositions.push_back(treePosition);
	}
	return treePositions;
}
// Gerar uma posição randomica
// Armazenar essa posição
// Passar as posições
// Desenhar