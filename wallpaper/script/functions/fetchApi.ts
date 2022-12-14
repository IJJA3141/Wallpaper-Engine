interface ramObj{
  size: number;
  used: number;
  presentage: number;
}

interface diskObj{
  name: string;
  size: number;
  freeSize: number;
}

interface dataConst {
  ram: ramObj;
  notes: Array<string>;
  disk: Array<diskObj>;
  cpu: number;
}

interface dataRefresh {
  ram: ramObj;
  cpu: number;
}

async function getConst():Promise<dataConst> {
  return fetch("http://localhost:23112/getConst", {method:"GET"}).then((res) => {
    return res.json();
  });
}

async function getRefresh():Promise<dataRefresh> {
  return fetch("http://localhost:23112/refresh", {method: "GET"}).then((res) => {
    return res.json();
  })
}

async function saveNotes(notes: string):Promise<Boolean> {
  return fetch("http://localhost:23112/write", {method: "POST", body: notes}).then((res) => {
    return res.json();
  })
}

export { getConst, getRefresh, saveNotes, dataConst, dataRefresh };