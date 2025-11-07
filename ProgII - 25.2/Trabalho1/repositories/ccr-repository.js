const model = require("../models");

const obterTodosCcrs = async () => {
    return await model.Ccr.findAll();
};

// Função para obter ccr por ID
const obterCcrPorId = async (ccr) => {
    return await model.Ccr.findByPk(ccr.id);
};

// Função para criar um novo ccr
const criarCcr = async (ccr) => {
    await model.Ccr.create(ccr);
    return ccr;
};

// Função para atualizar um ccr
const atualizarCcr = async (ccr) => {
    try {
        // Atualizar o ccr
        await model.Ccr.update(ccr, { where: { id: ccr.id } });

        // Retornar o ccr atualizado
        return await model.Ccr.findByPk(ccr.id);
    } catch (error) {
        throw error;
    }
};

// Função para deletar um ccr
const deletarCcr = async (ccr) => {
    try {
        // Deletar o ccr
        await model.Ccr.destroy({ where: { id: ccr.id } });

        return ccr;
    } catch (error) {
        throw error;
    }
};

// Função para obter matricula por ID do curso
const obterCcrPorIdCurso = async (id_curso) => {
    return await model.Ccr.findAll({
        where: {
            id_curso: id_curso,
        }
    });
};

module.exports = {
    obterTodosCcrs,
    obterCcrPorId,
    criarCcr,
    atualizarCcr,
    deletarCcr,
    obterCcrPorIdCurso,
};
