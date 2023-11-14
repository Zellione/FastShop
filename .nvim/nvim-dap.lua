local dap = require("dap")

dap.adapters.lldb = {
  type = 'executable',
  command = '/usr/bin/lldb-vscode', -- adjust as needed, must be absolute path
  name = 'lldb'
}

dap.configurations.cpp = {
  {
    name = 'Launch Backend Debug',
    type = 'lldb',
    request = 'launch',
    program = vim.fn.getcwd() .. '/backend/build/default/FastShop',
    cwd = '${workspaceFolder}/backend/build/default',
    stopOnEntry = false,
    args = {},
  },
}
