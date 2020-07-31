#include <Slender.h>

/*********************************
NAO PODE OLHAR PRA ELE
ELE APARECE CONFORME DETERMINADO EVENTO
	*DEPENDENDO DO TIPO DE PISTA, ELE APARECE E NÃO DEIXA PEGAR
OBVIO QUE VAI TER CRONOMETRO PRA ELE APARECER
	*MAS ELE APARECE CONFORME PISTAS VÃO SENDO COLETADAS
**********************************/

Slender::Slender() {
	slenderModel = std::make_unique<Model>("../images/scene.gltf");
}

double Slender::timeElapsed() {
	return glfwGetTime();
}

float Slender::position() {
	srand(0);
	float pos = rand() % 10;

	return pos;
}

/*----------SLENDER APPEARENCE-------------*/
// Uses used the time elapsed to count every second that 
// Slender will appear or not.
void Slender::slenderMechanics(Shader& slenderShader) {
	auto time = timeElapsed();

	float xPosition = position();
	float zPosition = position();
	
	std::cout << timeElapsed() << std::endl;

	//the slender will appear each "multiplier(i) * 10"
	if (timeElapsed() >= time_aux) {
		showSlender = !showSlender;
		i += 1.0;
		time_aux += (i * 10);
	}

	if (showSlender) {

		showSlender = true;
		slenderShader.useShader();
		glm::mat4 model = glm::mat4(1.0f);
		model = translate(model, glm::vec3(2.0, 1.4, 5.0));
		model = scale(model, glm::vec3(1.5, 1.5, 1.5));
		slenderShader.setMat4("model", model);

		std::cout << "Slender == " << xPosition << " " << zPosition << std::endl;

		glEnable(GL_FRAMEBUFFER_SRGB);
		slenderModel->Draw(slenderShader);
	}
}