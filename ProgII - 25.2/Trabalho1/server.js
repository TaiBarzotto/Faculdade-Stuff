const express = require("express");
const cors = require("cors");
const alunoRouter = require("./controllers/aluno-controller");
const professorRouter = require("./controllers/professor-controller");
const cursoRouter = require("./controllers/curso-controller");
const ccrRouter = require("./controllers/ccr-controller");
const matriculaRouter = require("./controllers/matricula-controller");
const professorCcrRouter = require("./controllers/professorCcr-controller");

const app = express();
app.use(cors());
app.use(express.json());

const PORT = 3002;
app.listen(PORT, () => console.log(`Servidor está rodando na porta ${PORT}.`));

app.use("/aluno", alunoRouter);
app.use("/professor", professorRouter);
app.use("/curso", cursoRouter);
app.use("/ccr", ccrRouter);
app.use("/matricula", matriculaRouter);
app.use("/professorCcr", professorCcrRouter);
