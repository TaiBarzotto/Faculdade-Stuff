const model = require("../models");

// Função para obter todos os professores
const obterTodosProfessores = async () => {
    return await model.Professor.findAll();
};

// Função para obter professor por ID
const obterProfessorPorId = async (professor) => {
    return await model.Professor.findByPk(professor.id);
};

// Função para criar um novo professor
const criarProfessor = async (professor) => {
    await model.Professor.create(professor);
    return professor;
};

// Função para atualizar um professor
const atualizarProfessor = async (professor) => {
    try {
        // Atualizar o professor
        await model.Professor.update(professor, { where: { id: professor.id } });

        // Retornar o professor atualizado
        return await model.Professor.findByPk(professor.id);
    } catch (error) {
        throw error;
    }
};

// Função para deletar um professor
const deletarProfessor = async (professor) => {
    try {
        // Deletar o professor
        await model.Professor.destroy({ where: { id: professor.id } });
        return professor;
    } catch (error) {
        throw error;
    }
};

module.exports = {
    obterTodosProfessores,
    obterProfessorPorId,
    criarProfessor,
    atualizarProfessor,
    deletarProfessor,
};
