import { useState, useEffect } from 'react'
import axios from "axios"
import Stack from '@mui/material/Stack';


export default function Aluno() {
  const [alunos, setAlunos] = useState([]);
  const [novoAluno, setNovoAluno] = useState("");
  const [novoAlunoEmail, setNovoAlunoEmail] = useState("");
  const [idAluno, setIdAluno] = useState("");

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
    try{
      const response = await axios.post("http://localhost:3002/aluno", {
        nome: novoAluno,
        email: novoAlunoEmail
      });
      buscaAlunos();
      console.log(response.data)
    } catch(error){
      console.log(error);
    }
  };

  const deletaAluno = async (id) => {
    try {
      await axios.delete(`http://localhost:3002/aluno/${id}`)
      buscaAlunos();
    } catch (error) {
      console.log(error);
    }
  };

  const atualizaAluno = async () => {
    try{
      let id = idAluno;
      const response = await axios.put(`http://localhost:3002/aluno/${id}`, {
        id: id,
        nome: novoAluno,
        email: novoAlunoEmail
      });
      buscaAlunos();
      console.log(response.data)
    } catch(error){
      console.log(error);
    }
  };


  return (<>
    {alunos.length > 0 && <ul>
      {alunos.map((aluno) => {
        return <li key={aluno.id}>{aluno.id} - {aluno.nome}
          <button
            style={{ marginLeft: 10 }}
            onClick={() => setIdAluno(aluno.id)}
          >
            Editar
          </button>

          <button
            style={{ marginLeft: 10 }}
            className="btnExcluir"
onClick={() => { deletaAluno(aluno.id); }}
          >
            Excluir
          </button>
        </li>;
      })}
    </ul>}
    <h3>{idAluno ? "Atualizar aluno" : "Cadastrar novo aluno"}</h3>

    <Stack spacing={1}>
      <Stack spacing={1} direction="row">
        <label>Nome do Aluno: </label>
        <input type="text" value={novoAluno} onChange={(event) => setNovoAluno(event.target.value)} />
      </Stack>
      <Stack spacing={1} direction="row">
        <label>Email do Aluno: </label>
        <input type="text" value={novoAlunoEmail} onChange={(event) => setNovoAlunoEmail(event.target.value)} />
      </Stack>
      <Stack spacing={1} direction="row">
        <button onClick={cadastrarAluno} disabled={idAluno !== ""}>
          Cadastrar
        </button>

        <button onClick={atualizaAluno} disabled={idAluno === ""}>
          Atualizar
        </button>
      </Stack>
    </Stack>
  </>)

}
