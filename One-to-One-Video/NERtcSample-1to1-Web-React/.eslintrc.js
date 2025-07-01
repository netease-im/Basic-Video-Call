module.exports = {
  parser: '@typescript-eslint/parser',
  extends: [
    'eslint:recommended', // ESLint 推荐规则
    'plugin:react/recommended',
    'plugin:@typescript-eslint/recommended',
    'prettier',
    'plugin:prettier/recommended', // 继承 Prettier 规则
  ],
  plugins: ['react', 'react-hooks', '@typescript-eslint', 'prettier'],
  env: {
    browser: true,
    es6: true,
    node: false,
  },
  settings: {
    react: {
      version: 'detect',
    },
  },
  rules: {
    // 自定义规则（可选）
    'react/react-in-jsx-scope': 'off',
    'react-hooks/rules-of-hooks': 'error',
    'react-hooks/exhaustive-deps': 'warn',
    'prettier/prettier': 'error',
    '@typescript-eslint/explicit-module-boundary-types': 'off',
  },
};
