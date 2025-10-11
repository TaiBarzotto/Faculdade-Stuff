const model = require("../models");

// Função para obter todos os alunos
const obterTodosAlunos = async () => {
	return await model.Aluno.findAll();
};

// Função para obter aluno por ID
const obterAlunoPorId = async (aluno) => {
	return await model.Aluno.findByPk(aluno.id);
};

// Função para criar um novo aluno
const criarAluno = async (aluno) => {
	await model.Aluno.create(aluno);
	return aluno;
};

// Função para atualizar um aluno
const atualizarAluno = async (aluno) => {
	try {
		// Atualizar o aluno
		await model.Aluno.update(aluno, { where: { id: aluno.id } });

		// Retornar o aluno atualizado
		return await model.Aluno.findByPk(aluno.id);
	} catch (error) {
		throw error;
	}
};

// Função para deletar um aluno
const deletarAluno = async (aluno) => {
	try {
		// Deletar o aluno
		await model.Aluno.destroy({ where: { id: aluno.id } });
		return aluno;
	} catch (error) {
		throw error;
	}
};

module.exports = {
	obterTodosAlunos,
	obterAlunoPorId,
	criarAluno,
	atualizarAluno,
	deletarAluno,
};
