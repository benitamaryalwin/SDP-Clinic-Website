
const express = require("express");
const { spawn } = require("child_process");
const path = require("path");

const app = express();
app.use(express.json({limit:"2mb"}));
app.use(express.static(path.join(__dirname,"public")));

function run(mode, input="") {
  return new Promise((resolve, reject) => {
    const exe = process.platform === "win32" ? "clinic_store.exe" : "./clinic_store";
    const p = spawn(exe, [mode], {cwd: __dirname});

    let out="", err="";
    p.stdout.on("data", d => out += d.toString());
    p.stderr.on("data", d => err += d.toString());

    p.on("close", code => code === 0 ? resolve(out) : reject(err));

    if (input) p.stdin.write(input);
    p.stdin.end();
  });
}

app.get("/api/data", async (_, res) => {
  try { res.type("json").send(await run("read")); }
  catch (e) { res.status(500).json({error:String(e)}); }
});

app.post("/api/data", async (req, res) => {
  try { res.type("json").send(await run("write", JSON.stringify(req.body || {}))); }
  catch (e) { res.status(500).json({error:String(e)}); }
});

app.listen(3000, () => console.log("http://localhost:3000/MediCare_Pro.html"));
