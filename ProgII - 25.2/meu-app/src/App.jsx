import { useState, useEffect } from 'react'
import './App.css'
import Curso from './Curso'
import Aluno from './Aluno'
import Professor from './Professor'
import Ccr from './Ccr'
import Matricula from './Matricula'
import ProfessorCcr from './ProfessorCcr'
import Titulo from './Titulo'
import Stack from '@mui/material/Stack';

export default function App() {
  const [exibirCursos, setExibirCursos] = useState(true);
  const [exibirAlunos, setExibirAlunos] = useState(true);
  const [exibirProfessor, setExibirProfessor] = useState(true);
  const [exibirCcr, setExibirCcr] = useState(true);
  const [exibirMatricula, setExibirMatricula] = useState(true);
  const [exibirProfessorCcr, setExibirProfessorCcr] = useState(true);

  const controlaCursos = () => setExibirCursos(!exibirCursos);
  const controlaAlunos = () => setExibirAlunos(!exibirAlunos);
  const controlaProfessor = () => setExibirProfessor(!exibirProfessor);
  const controlaCcr = () => setExibirCcr(!exibirCcr);
  const controlaMatricula = () => setExibirMatricula(!exibirMatricula);
  const controlaProfessorCcr = () => setExibirProfessorCcr(!exibirProfessorCcr);

  useEffect(() => {
    if (exibirCursos) {
      setExibirAlunos(false);
      setExibirProfessor(false);
      setExibirCcr(false);
      setExibirMatricula(false);
      setExibirProfessorCcr(false);
    }
  }, [exibirCursos]);

  useEffect(() => {
    if (exibirAlunos) {
      setExibirCursos(false);
      setExibirProfessor(false);
      setExibirCcr(false);
      setExibirMatricula(false);
      setExibirProfessorCcr(false);
    }
  }, [exibirAlunos]);

  useEffect(() => {
    if (exibirProfessor) {
      setExibirCursos(false);
      setExibirAlunos(false);
      setExibirCcr(false);
      setExibirMatricula(false);
      setExibirProfessorCcr(false);
    }
  }, [exibirProfessor]);

  useEffect(() => {
    if (exibirCcr) {
      setExibirCursos(false);
      setExibirAlunos(false);
      setExibirProfessor(false);
      setExibirMatricula(false);
      setExibirProfessorCcr(false);
    }
  }, [exibirCcr]);

  useEffect(() => {
    if (exibirMatricula) {
      setExibirCursos(false);
      setExibirAlunos(false);
      setExibirProfessor(false);
      setExibirCcr(false);
      setExibirProfessorCcr(false);
    }
  }, [exibirMatricula]);

  useEffect(() => {
    if (exibirProfessorCcr) {
      setExibirCursos(false);
      setExibirAlunos(false);
      setExibirProfessor(false);
      setExibirCcr(false);
      setExibirMatricula(false);
    }
  }, [exibirProfessorCcr]);
  return (
    <>
      {<Titulo />}
      <Stack>
        <button onClick={controlaCursos} type="submit">Ver Cursos</button>
        {exibirCursos && <Curso />}

        <br/>
        <button onClick={controlaAlunos} type="submit">Ver Alunos</button>
        {exibirAlunos && <Aluno />}

        <br/>
        <button onClick={controlaProfessor} type="submit">Ver Professores</button>
        {exibirProfessor && <Professor />}

        <br/>
        <button onClick={controlaCcr} type="submit">Ver Ccrs</button>
        {exibirCcr && <Ccr />}

        <br/>
        <button onClick={controlaMatricula} type="submit">Ver Matriculas</button>
        {exibirMatricula && <Matricula />}

        <br/>
        <button onClick={controlaProfessorCcr} type="submit">Ver ProfessorCcrs</button>
        {exibirProfessorCcr && <ProfessorCcr />}
      </Stack>
    </>
  )
}

