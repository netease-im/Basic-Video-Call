module.exports = {
  root: true,
  env: {
      node: true
  },
  extends: [
      'plugin:vue/essential',
      '@vue/standard'
  ],
  parserOptions: {
      parser: 'babel-eslint'
  },
  rules: {
      'no-console': process.env.NODE_ENV === 'production' ? 'warn' : 'off',
      'no-debugger': process.env.NODE_ENV === 'production' ? 'warn' : 'off',
      'space-in-parens': 0,
      'no-multiple-empty-lines': 0,
      indent: 'off', //['error', 4],
      semi: 0,
      quotes: [2, 'single'],
      'comma-dangle': 0,
      'space-before-function-paren': 0,
      'block-spacing': 0,
      'space-before-blocks': 0,
      'spaced-comment': 0,
      'no-unused-vars': 'off',
      'import/no-named-as-default': 'off',
      'import/prefer-default-export': 'off',
      'vue/script-indent': ['error', 4, {
          baseIndent: 1
      }]
  },
  overrides: [
      {
          files: ['*.vue'],
          rules: {
              indent: 'off'
          }
      },
      {
          files: [
              '**/__tests__/*.{j,t}s?(x)',
              '**/tests/unit/**/*.spec.{j,t}s?(x)',
          ],
          env: {
              jest: true
          }
      }
  ]
}
