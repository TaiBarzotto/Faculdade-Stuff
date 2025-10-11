const professorCcrRepository = require("../repositories/professorCcr-repository");

// Função para retornar todas as professorCcrs
const retornaTodosProfessorCcrs = async (req, res) => {
    try {
        const professorCcrs = await professorCcrRepository.obterTodosProfessorCcrs();
        res.status(200).json({ professorCcrs: professorCcrs });
    } catch (error) {
        console.log("Erro ao buscar professorCcrs:", error);
        res.sendStatus(500);
    }
};

// Função para retornar todas as professorCcrs do professor
const retornaProfessorCcrProfessor = async (req, res) => {
    try {
        const professorCcrs = await professorCcrRepository.obterprofessorCcrPorIdProfessor(req.params.id_professor);
        res.status(200).json({ professorCcrs: professorCcrs });
    } catch (error) {
        console.log("Erro ao buscar professorCcrs:", error);
        res.sendStatus(500);
    }
};

// Função para retornar todas as professorCcrs do ccr
const retornaTodosProfessorCcrsCcr = async (req, res) => {
    try {
        const professorCcrs = await professorCcrRepository.obterprofessorCcrPorIdCcr(req.params.id_ccr);
        res.status(200).json({ professorCcrs: professorCcrs });
    } catch (error) {
        console.log("Erro ao buscar professorCcrs:", error);
        res.sendStatus(500);
    }
};

// Função para criar um nova professorCcr
const criaProfessorCcr = async (req, res) => {
    const { id_professor, id_ccr } = req.body;
    try {
        if (!id_professor || !id_ccr) {
            return res
                .status(400)
                .json({ message: "ID do professor e ccr são obrigatórios." });
        }

        const professorCcr = await professorCcrRepository.criarProfessorCcr({
            id_professor,
            id_ccr,
        });
        res.status(201).json(professorCcr);
    } catch (error) {
        console.log("Erro ao criar professorCcr:", error);
        res.sendStatus(500);
    }
};

// Função para atualizar uma professorCcr
const atualizaProfessorCcr = async (req, res) => {
    const { id_ccr } = req.body;
    const id_professor = parseInt(req.params.id_professor);

    try {
        const professorCcrAtualizada =
            await professorCcrRepository.atualizarProfessorCcr({
                id_professor,
                id_ccr,
            });

        if (professorCcrAtualizada) {
            res.status(200).json(professorCcrAtualizada);
        } else {
            res.status(404).json({ message: "professorCcr não encontrada" });
        }
    } catch (error) {
        console.log("Erro ao atualizar professorCcr:", error);
        res.sendStatus(500);
    }
};

// Função para deletar uma professorCcr
const deletaProfessorCcr = async (req, res) => {
    try {
        const id_professor = parseInt(req.params.id_professor);
        const professorCcrRemovida = await professorCcrRepository.deletarProfessorCcr(id_professor);

        if (professorCcrRemovida) {
            res.status(200).json({
                message: "professorCcr removida com sucesso.",
                professorCcr: professorCcrRemovida,
            });
        } else {
            res.status(404).json({ message: "professorCcr não encontrada" });
        }
    } catch (error) {
        console.error("Erro ao deletar professorCcr:", error);
        res.status(500).json({ message: "Erro ao deletar professorCcr" });
    }
};

module.exports = {
    retornaTodosProfessorCcrs,
    retornaProfessorCcrProfessor,
    retornaTodosProfessorCcrsCcr,
    criaProfessorCcr,
    atualizaProfessorCcr,
    deletaProfessorCcr,
};
