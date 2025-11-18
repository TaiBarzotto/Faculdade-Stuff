const model = require("../models");

// Função para obter todos as ProfessorCcrs
const obterTodosProfessorCcrs = async () => {
    return await model.ProfessorCcr.findAll({
        include: [
            {
                model: model.Professor,
            },
            {
                model: model.Ccr
            }
        ]
    });
};

// Função para obter ProfessorCcr por ID do professor
const obterProfessorCcrPorIdProfessor = async (id_professor) => {
    return await model.ProfessorCcr.findAll({
        where: {
            id_professor: id_professor,
        },
        include: [
            {
                model: model.Ccr,
            },
        ],
    });
};

// Função para obter ProfessorCcr por ID do ccr
const obterProfessorCcrPorIdCcr = async (id_ccr) => {
    return await model.ProfessorCcr.findAll({
        where: {
            id_ccr: id_ccr,
        },
        include: [
            {
                model: model.Professor,
            },
        ],
    });
};

// Função para criar uma nova ProfessorCcr
const criarProfessorCcr = async (ProfessorCcr) => {
    await model.ProfessorCcr.create(ProfessorCcr);
    return ProfessorCcr;
};

// Função para atualizar uma ProfessorCcr
const atualizarProfessorCcr = async (ProfessorCcr) => {
    try {
        // Atualizar o professor
        await model.ProfessorCcr.update(ProfessorCcr, {
            where: { id_professor: ProfessorCcr.id_professor },
        });

        // Retornar a ProfessorCcr atualizada
        return await model.ProfessorCcr.findByPk(ProfessorCcr.id_professor);
    } catch (error) {
        throw error;
    }
};

// Função para deletar uma ProfessorCcr
const deletarProfessorCcr = async (id_professor) => {
    try {
        const ProfessorCcr = await obterProfessorCcrPorIdProfessor(id_professor);
        // Deletar o professor
        await model.ProfessorCcr.destroy({ where: { id_professor: id_professor } });

        return ProfessorCcr;
    } catch (error) {
        throw error;
    }
};

module.exports = {
    obterTodosProfessorCcrs,
    obterProfessorCcrPorIdProfessor,
    obterProfessorCcrPorIdCcr,
    criarProfessorCcr,
    atualizarProfessorCcr,
    deletarProfessorCcr,
};
