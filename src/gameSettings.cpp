#include <gameSettings.h>

gameSettings::gameSettings(Shader& shader, Camera& camera, Model& model)
	: shaderProgram(shader), camera(camera), model(model)
	{ }

void gameSettings::showSlender(int time_elaps) {
	if (time_elaps >= frequency) {
		times += 0.5;
		frequency += (times * 10);
		
		cout << "passs here" << endl;
		//cout << "passs here" << endl;
		//cout << "passs here" << endl;

		shaderProgram.use();
		camera.transform(&shaderProgram);

		glm::mat4 matriz_model = glm::mat4(1.0f);
		matriz_model = glm::translate(matriz_model, glm::vec3(0.0f, -1.0f, 0.0f));
		matriz_model = glm::scale(matriz_model, glm::vec3(1.0f, 1.0f, 1.0f));
		shaderProgram.setMat4("model", matriz_model);
		model.Draw(shaderProgram);
	}
}