import { useState, useEffect } from 'react'
import axios from "axios"
import Stack from '@mui/material/Stack';


export default function Aluno() {
  const [alunos, setAlunos] = useState([]);
  const [novoAluno, setNovoAluno] = useState("");
  const [novoAlunoEmail, setNovoAlunoEmail] = useState("");


  const buscaAlunos = async () => {
    try {
      const response = await axios.get("http://localhost:3002/aluno/todos");
      console.log(response.data);
      setAlunos(response.data.alunos);
    }
    catch (error) {
      console.log(error);
      setAlunos([]);
    }
  }

  useEffect(
    () => {
      buscaAlunos();
    },
    []);

  const cadastrarAluno = async () => {
    const response = await axios.post("http://localhost:3002/aluno", {
      nome: novoAluno,
      email: novoAlunoEmail
    });
    console.log(response.data)
  }


  return (<>
    {alunos.length > 0 && <ul>
      {alunos.map((aluno) => {
        return <li key={aluno.id}>{aluno.nome}</li>;
      })}
    </ul>}
    <Stack spacing={1}>
      <Stack spacing={1} direction="row">
        <label>Nome do Aluno: </label>
        <input type="text" value={novoAluno} onChange={(event) => setNovoAluno(event.target.value)} />
      </Stack>
      <Stack spacing={1} direction="row">
        <label>Email do Aluno: </label>
        <input type="text" value={novoAlunoEmail} onChange={(event) => setNovoAlunoEmail(event.target.value)} />
      </Stack>
      <button onClick={cadastrarAluno} type="submit">Cadastrar Aluno</button>
    </Stack>  
    </>)

}
