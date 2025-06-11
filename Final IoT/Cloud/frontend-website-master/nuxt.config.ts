// https://nuxt.com/docs/api/configuration/nuxt-config
import tailwindcss from '@tailwindcss/vite'

export default defineNuxtConfig({

    modules: ['@nuxt/eslint'],
    devtools: { enabled: false },
    css: ['~/assets/css/tailwind.css'], compatibilityDate: '2025-05-15',
    vite: {
        plugins: [
            tailwindcss(),
        ],
    },
    eslint: {
        config: {
            stylistic: {
                indent: 4,
            },
        },
    },
})
