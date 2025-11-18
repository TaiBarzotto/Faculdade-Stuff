import { useState, useEffect } from 'react'
import axios from "axios"
import Stack from '@mui/material/Stack';


export default function ProfessorCcr() {
  const [professorCcrs, setProfessorCcrs] = useState([]);
  const [novoIdProfessor, setNovoIdProfessor] = useState("");
  const [novoIdCcr, setNovoIdCcr] = useState("");
  const [idProfessorCcr, setIdProfessorCcr] = useState("");

  const buscaProfessorCcrs = async () => {
    try {
      const response = await axios.get("http://localhost:3002/professorCcr/");
      console.log(response.data);
      setProfessorCcrs(response.data.professorCcrs);
    }
    catch (error) {
      console.log(error);
    }
  }

  useEffect(
    () => {
      buscaProfessorCcrs();
    },
    []
  )

  const cadastrarProfessorCcr = async () => {
    try{
      const response = await axios.post("http://localhost:3002/professorCcr", {
        id_professor: novoIdProfessor,
        id_ccr: novoIdCcr
      });
      buscaProfessorCcrs()
      console.log(response.data)
    } catch(error){
      console.log(error);
    }
  };

  const deletaProfessorCcr = async (id) => {
    try {
      await axios.delete(`http://localhost:3002/professorCcr/${id}`)
      buscaProfessorCcrs();
    } catch (error) {
      console.log(error);
    }
  };

  const atualizaProfessorCcr = async () => {
    try{
      let id = novoIdProfessor;
      const response = await axios.put(`http://localhost:3002/professorCcr/${id}`, {
        id_professor: novoIdProfessor,
        id_ccr: novoIdCcr
      });
      buscaProfessorCcrs();
      console.log(response.data)
    } catch(error){
      console.log(error);
    }
  };

  return (<>
    <ul>
      {professorCcrs.map((professorCcr) => {
        return <li key={professorCcr.id_ccr}>{professorCcr.Professor.nome} - {professorCcr.Ccr.descricao}
          <button
            style={{ marginLeft: 10 }}
            onClick={() => setIdProfessorCcr(professorCcr.id_professor)}
          >
            Editar
          </button>

          <button
            style={{ marginLeft: 10 }}
            className="btnExcluir"
            onClick={() => { deletaProfessorCcr(professorCcr.id_professor); }}
          >
            Excluir
          </button>
        </li>;
      })}
    </ul>
    <h3>{idProfessorCcr ? "Atualizar Professor-Ccr" : "Cadastrar novo Professor-Ccr"}</h3>

    <Stack spacing={1}>
      <Stack spacing={1} direction="row">
        <label>Id do Professor: </label>
        <input type="text" value={novoIdProfessor} onChange={(event) => setNovoIdProfessor(event.target.value)} />
      </Stack>
      <Stack spacing={1} direction="row">
        <label>Id do Ccr: </label>
        <input type="text" value={novoIdCcr} onChange={(event) => setNovoIdCcr(event.target.value)} />
      </Stack>
      <Stack spacing={1} direction="row">
        <button onClick={cadastrarProfessorCcr} disabled={idProfessorCcr !== ""}>
          Cadastrar
        </button>

        <button onClick={atualizaProfessorCcr} disabled={idProfessorCcr === ""}>
          Atualizar
        </button>
      </Stack>
    </Stack>
  </>)

}
