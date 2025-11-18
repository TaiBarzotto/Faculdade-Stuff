import { useState, useEffect } from 'react'
import axios from "axios"
import Stack from '@mui/material/Stack';


export default function Ccr() {
  const [ccrs, setCcrs] = useState([]);
  const [novoCcrEmenta, setNovoCcrEmenta] = useState("");
  const [novoCcrDescricao, setNovoCcrDescricao] = useState("");
  const [novoCcrIdCurso, setNovoCcrIdCurso] = useState("");
  const [idCcr, setIdCcr] = useState("");

  const buscaCcrs = async () => {
    try {
      const response = await axios.get("http://localhost:3002/ccr/todos");
      console.log(response.data);
      setCcrs(response.data.ccr);
    }
    catch (error) {
      console.log(error);
    }
  }

  useEffect(
    () => {
      buscaCcrs();
    },
    []
  )

  const cadastrarCcr = async () => {
    try {
      const response = await axios.post("http://localhost:3002/ccr", {
        descricao: novoCcrDescricao,
        ementa: novoCcrEmenta,
        id_curso: novoCcrIdCurso
      });
      buscaCcrs();
      console.log(response.data)
    } catch (error) {
      console.log(error);
    }
  };

  const deletaCcr = async (id) => {
    try {
      await axios.delete(`http://localhost:3002/ccr/${id}`)
      buscaCcrs();
    } catch (error) {
      console.log(error);
    }
  };

  const atualizaCcr = async () => {
    try {
      let id = idCcr;
      const response = await axios.put(`http://localhost:3002/ccr/${id}`, {
        id: id,
        descricao: novoCcrDescricao,
        ementa: novoCcrEmenta,
        id_curso: novoCcrIdCurso
      });
      buscaCcrs();
      console.log(response.data)
    } catch (error) {
      console.log(error);
    }
  };


  return (<>
    {ccrs.length > 0 && <ul>
      {ccrs.map((ccr) => {
        return <li key={ccr.id}>{ccr.id} - {ccr.descricao} - {ccr.ementa} - {ccr.Curso.descricao}
          <button
            style={{ marginLeft: 10 }}
            onClick={() => setIdCcr(ccr.id)}
          >
            Editar
          </button>

          <button
            style={{ marginLeft: 10 }}
            className="btnExcluir"
            onClick={() => { deletaCcr(ccr.id); }}
          >
            Excluir
          </button>
        </li>;
      })}
    </ul>}
    <h3>{idCcr ? "Atualizar ccr" : "Cadastrar novo ccr"}</h3>

    <Stack spacing={1}>
      <Stack spacing={1} direction="row">
        <label>Descrição do ccr: </label>
        <input type="text" value={novoCcrDescricao} onChange={(event) => setNovoCcrDescricao(event.target.value)} />
      </Stack>
      <Stack spacing={1} direction="row">
        <label>Ementa do ccr: </label>
        <input type="text" value={novoCcrEmenta} onChange={(event) => setNovoCcrEmenta(event.target.value)} />
      </Stack>
      <Stack spacing={1} direction="row">
        <label>Id do Curso do ccr: </label>
        <input type="text" value={novoCcrIdCurso} onChange={(event) => setNovoCcrIdCurso(event.target.value)} />
      </Stack>
      <Stack spacing={1} direction="row">
        <button onClick={cadastrarCcr} disabled={idCcr !== ""}>
          Cadastrar
        </button>

        <button onClick={atualizaCcr} disabled={idCcr === ""}>
          Atualizar
        </button>
      </Stack>
    </Stack>
  </>)

}
