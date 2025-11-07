const ccrRepository = require("../repositories/ccr-repository");

// Função para retornar todos os ccr
const retornaTodosCcrs = async (req, res) => {
    try {
        const ccr = await ccrRepository.obterTodosCcrs();
        res.status(200).json({ ccr: ccr });
    } catch (error) {
        console.log("Erro ao buscar ccr:", error);
        res.sendStatus(500);
    }
};

// Função para criar um novo ccr
const criaCcr = async (req, res) => {
    const { id, descricao, ementa, id_curso } = req.body;
    try {
        if (!id || !descricao || !ementa || !id_curso) {
            return res
                .status(400)
                .json({ message: "ID, descrição, ementa e id_curso são obrigatórios." });
        }

        const ccr = await ccrRepository.criarCcr({
            id,
            descricao,
            ementa,
            id_curso
        });
        res.status(201).json(ccr);
    } catch (error) {
        console.log("Erro ao criar ccr:", error);
        res.sendStatus(500);
    }
};

// Função para atualizar um ccr
const atualizaCcr = async (req, res) => {
    const { descricao, ementa, id_curso } = req.body;
    const id = parseInt(req.params.id);
    try {
        const ccrAtualizado = await ccrRepository.atualizarCcr({
            id,
            descricao,
            ementa, 
            id_curso
        });

        if (ccrAtualizado) {
            res.status(200).json(ccrAtualizado);
        } else {
            res.status(404).json({ message: "ccr não encontrado" });
        }
    } catch (error) {
        console.log("Erro ao atualizar ccr:", error);
        res.sendStatus(500);
    }
};

// Função para deletar um ccr
const deletaCcr = async (req, res) => {
    try {
        const id = parseInt(req.params.id);
        const ccrRemovido = await ccrRepository.deletarCcr({ id });

        if (ccrRemovido) {
            res.status(200).json({
                message: "ccr removido com sucesso.",
                ccr: ccrRemovido,
            });
        } else {
            res.status(404).json({ message: "ccr não encontrado" });
        }
    } catch (error) {
        console.error("Erro ao deletar ccr:", error);
        res.status(500).json({ message: "Erro ao deletar ccr" });
    }
};

// Função para buscar ccr por ID
const retornaCcrPorId = async (req, res) => {
    try {
        const id = parseInt(req.params.id);
        const ccr = await ccrRepository.obterCcrPorId({
            id,
        });

        if (ccr) {
            res.status(200).json(ccr);
        } else {
            res.status(404).json({ message: "ccr não encontrado." });
        }
    } catch (error) {
        console.log("Erro ao buscar ccr:", error);
        res.sendStatus(500);
    }
};

// Função para retornar todas as ccrs do curso
const retornaTodasCcrsCurso = async (req, res) => {
    try {
        const ccrs = await ccrRepository.obterCcrPorIdCurso(req.params.id_curso);
        res.status(200).json({ ccrs: ccrs });
    } catch (error) {
        console.log("Erro ao buscar ccrs:", error);
        res.sendStatus(500);
    }
};

module.exports = {
    retornaTodosCcrs,
    criaCcr,
    atualizaCcr,
    deletaCcr,
    retornaCcrPorId,
    retornaTodasCcrsCurso,
};
