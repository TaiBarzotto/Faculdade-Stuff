import { useState, useEffect } from 'react'
import axios from "axios"
import Stack from '@mui/material/Stack';


export default function Professor() {
  const [professores, setProfessores] = useState([]);
  const [novoProfessor, setNovoProfessor] = useState("");
  const [novoProfessorEmail, setNovoProfessorEmail] = useState("");
  const [idProfessor, setIdProfessor] = useState("");

  const buscaProfessores = async () => {
    try {
      const response = await axios.get("http://localhost:3002/professor/todos");
      console.log(response.data);
      setProfessores(response.data.professores);
    }
    catch (error) {
      console.log(error);
      setProfessores([]);
    }
  }

  useEffect(
    () => {
      buscaProfessores();
    },
    []
  )

  const cadastrarProfessor = async () => {
    try{
      const response = await axios.post("http://localhost:3002/professor", {
        nome: novoProfessor,
        email: novoProfessorEmail
      });
      buscaProfessores();
      console.log(response.data)
    } catch(error){
      console.log(error);
    }
  };

  const deletaProfessor = async (id) => {
    try {
      await axios.delete(`http://localhost:3002/professor/${id}`)
      buscaProfessores();
    } catch (error) {
      console.log(error);
    }
  };

  const atualizaProfessor = async () => {
    try{
      let id = idProfessor;
      const response = await axios.put(`http://localhost:3002/professor/${id}`, {
        id: id,
        nome: novoProfessor,
        email: novoProfessorEmail
      });
      buscaProfessores();
      console.log(response.data)
    } catch(error){
      console.log(error);
    }
  };


  return (<>
    {professores.length > 0 && <ul>
      {professores.map((professor) => {
        return <li key={professor.id}>{professor.id} - {professor.nome}
          <button
            style={{ marginLeft: 10 }}
            onClick={() => setIdProfessor(professor.id)}
          >
            Editar
          </button>

          <button
            style={{ marginLeft: 10 }}
            className="btnExcluir"
            onClick={() => { deletaProfessor(professor.id); }}
          >
            Excluir
          </button>
        </li>;
      })}
    </ul>}
    <h3>{idProfessor ? "Atualizar professor" : "Cadastrar novo professor"}</h3>

    <Stack spacing={1}>
      <Stack spacing={1} direction="row">
        <label>Nome do Professor: </label>
        <input type="text" value={novoProfessor} onChange={(event) => setNovoProfessor(event.target.value)} />
      </Stack>
      <Stack spacing={1} direction="row">
        <label>Email do Professor: </label>
        <input type="text" value={novoProfessorEmail} onChange={(event) => setNovoProfessorEmail(event.target.value)} />
      </Stack>
      <Stack spacing={1} direction="row">
        <button onClick={cadastrarProfessor} disabled={idProfessor !== ""}>
          Cadastrar
        </button>

        <button onClick={atualizaProfessor} disabled={idProfessor === ""}>
          Atualizar
        </button>
      </Stack>
    </Stack>
  </>)

}
